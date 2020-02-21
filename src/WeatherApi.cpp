//============================================================================
/// \file   WeatherApi.cpp
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   07/02/2020
/// \brief  Implementation of the CWeatherApi class.
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherApi.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>

using namespace std;

static const auto BASE_URL =
    QStringLiteral("https://www.metaweather.com/api/location/");
static const auto LAST_LOCATION_NAME_SETTINGS_KEY =
    QStringLiteral("last_location_name");
static const auto LAST_LOCATION_WOEID_SETTINGS_KEY =
    QStringLiteral("last_location_woeid");
static const auto FAVOURITE_LOCATIONS_SETTINGS_GROUP =
    QStringLiteral("favourite_locations");

//=============================================================================
CWeatherApi::CWeatherApi(QObject* parent)
    : QObject{parent},
      m_NetAccessManager{make_unique<QNetworkAccessManager>(this)},
      m_NetReply{nullptr},
      m_NetRequest{make_unique<QNetworkRequest>()},
      m_WeatherDataModel{make_unique<CWeatherDataModel>(this)},
      m_Settings{make_unique<QSettings>(this)}
{
    // allow HTTP redirects (so the trailing '/' in URLs is not necessary)
    m_NetRequest->setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                               QNetworkRequest::NoLessSafeRedirectPolicy);

    // load last location's weather data if present
    const auto LastLocationName =
        m_Settings->value(LAST_LOCATION_NAME_SETTINGS_KEY).toString();
    if (!LastLocationName.isEmpty())
    {
        setLocationName(LastLocationName);
        m_LocationWOEID =
            m_Settings->value(LAST_LOCATION_WOEID_SETTINGS_KEY).toInt();
        requestWeatherData();
    }

    // load favourite locations
    m_Settings->beginGroup(FAVOURITE_LOCATIONS_SETTINGS_GROUP);
    const auto FavLocationNames = m_Settings->childKeys();
    for_each(
        begin(FavLocationNames), end(FavLocationNames), [this](const auto& name) {
            m_FavouriteLocations.insert(name, m_Settings->value(name).toInt());
        });
    m_Settings->endGroup();
    emit favouriteLocationsChanged();
}

//=============================================================================
CWeatherApi::~CWeatherApi()
{
    // save last location's weather data
    m_Settings->setValue(LAST_LOCATION_NAME_SETTINGS_KEY, m_LocationName);
    m_Settings->setValue(LAST_LOCATION_WOEID_SETTINGS_KEY, m_LocationWOEID);

    // save favourite locations
    m_Settings->beginGroup(FAVOURITE_LOCATIONS_SETTINGS_GROUP);
    foreach (const auto& Key, m_FavouriteLocations.keys())
    {
        m_Settings->setValue(Key, m_FavouriteLocations.value(Key));
    }
    m_Settings->endGroup();
}

//=============================================================================
QString CWeatherApi::locationName() const
{
    return m_LocationName;
}

//=============================================================================
CWeatherDataModel* CWeatherApi::weatherDataModel() const
{
    return m_WeatherDataModel.get();
}

//=============================================================================
QStringList CWeatherApi::favouriteLocations()
{
    return m_FavouriteLocations.keys();
}

//=============================================================================
void CWeatherApi::requestLocation(const QString& desiredLocation)
{
    m_NetRequest->setUrl({BASE_URL + "search/?query=" + desiredLocation});
    m_NetReply.reset(m_NetAccessManager->get(*m_NetRequest));

    connect(m_NetReply.get(), &QNetworkReply::readyRead, this,
            &CWeatherApi::onReadyRead);
    connect(this, &CWeatherApi::jsonReady, this, [this]() {
        auto LocationsJsonArray = m_ResponseJsonDoc.array();

        auto Locations = QStringList();
        for_each(begin(LocationsJsonArray), end(LocationsJsonArray),
                 [&Locations](const QJsonValue& val) {
                     const auto Location = val.toObject();
                     Locations.append(Location["title"].toString());
                 });
        emit locationsReady(Locations);
    });
    connect(m_NetReply.get(), &QNetworkReply::finished, this,
            &CWeatherApi::cleanUp);
}

//=============================================================================
void CWeatherApi::setLocationByIndex(int index)
{
    const auto Location = m_ResponseJsonDoc.array()[index].toObject();
    m_LocationWOEID = Location["woeid"].toInt();
    setLocationName(Location["title"].toString());
}

//=============================================================================
void CWeatherApi::setLocationByName(const QString& name)
{
    m_LocationWOEID = m_FavouriteLocations[name];
    setLocationName(name);
}

//=============================================================================
void CWeatherApi::requestWeatherData()
{
    m_NetRequest->setUrl({BASE_URL + QString::number(m_LocationWOEID)});
    m_NetReply.reset(m_NetAccessManager->get(*m_NetRequest));

    connect(m_NetReply.get(), &QNetworkReply::readyRead, this,
            &CWeatherApi::onReadyRead);
    connect(this, &CWeatherApi::jsonReady, this, [this]() {
        const auto WeatherDataJsonArray =
            m_ResponseJsonDoc.object().value("consolidated_weather").toArray();
        const auto TodaysWeatherData = WeatherDataJsonArray.first().toObject();
        m_WeatherDataModel->setData(0,
                               TodaysWeatherData["weather_state_name"].toVariant(),
                               CWeatherDataModel::WeatherStateNameRole);
        m_WeatherDataModel->setData(0,
                               TodaysWeatherData["weather_state_abbr"].toVariant(),
                               CWeatherDataModel::WeatherStateAbbrRole);
        m_WeatherDataModel->setData(0, TodaysWeatherData["the_temp"].toVariant(),
                               CWeatherDataModel::TheTempRole);
        m_WeatherDataModel->setData(0, TodaysWeatherData["min_temp"].toVariant(),
                               CWeatherDataModel::MinTempRole);
        m_WeatherDataModel->setData(0, TodaysWeatherData["max_temp"].toVariant(),
                               CWeatherDataModel::MaxTempRole);
        emit weatherDataModelChanged();
    });
    connect(m_NetReply.get(), &QNetworkReply::finished, this,
            &CWeatherApi::cleanUp);
}

//=============================================================================
void CWeatherApi::addCurrentLocationToFavourites()
{
    m_FavouriteLocations.insert(m_LocationName, m_LocationWOEID);
    emit favouriteLocationsChanged();
}

//=============================================================================
void CWeatherApi::onReadyRead()
{
    m_DataBuffer += m_NetReply->readAll();
    QJsonParseError Error;
    m_ResponseJsonDoc = QJsonDocument::fromJson(m_DataBuffer, &Error);
    if (m_ResponseJsonDoc.isNull())
    {
        qWarning() << "Could not parse received JSON data! The following "
                      "error occurred:"
                   << Error.errorString();
        return;
    }
    emit jsonReady();
}

//=============================================================================
void CWeatherApi::cleanUp()
{
    m_NetReply->deleteLater();
    m_NetReply = nullptr;
    m_DataBuffer.clear();
}

//=============================================================================
void CWeatherApi::setLocationName(const QString& locationName)
{
    m_LocationName = locationName;
    emit locationNameChanged();
}
