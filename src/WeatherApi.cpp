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

//=============================================================================
CWeatherApi::CWeatherApi(QObject* parent)
    : QObject{parent},
      m_NetAccessManager{make_unique<QNetworkAccessManager>(this)},
      m_NetReply{nullptr},
      m_NetRequest{make_unique<QNetworkRequest>()},
      m_WeatherData{make_unique<CWeatherData>(this)},
      m_Settings{make_unique<QSettings>(this)}
{
    m_NetRequest->setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                               QNetworkRequest::NoLessSafeRedirectPolicy);
}

//=============================================================================
CWeatherApi::~CWeatherApi() = default;

//=============================================================================
QString CWeatherApi::locationName() const
{
    return m_LocationName;
}

//=============================================================================
CWeatherData* CWeatherApi::weatherData() const
{
    return m_WeatherData.get();
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
        m_WeatherData->setWeatherStateName(
            TodaysWeatherData["weather_state_name"].toString());
        m_WeatherData->setTheTemp(TodaysWeatherData["the_temp"].toDouble());
        m_WeatherData->setMinTemp(TodaysWeatherData["min_temp"].toDouble());
        m_WeatherData->setMaxTemp(TodaysWeatherData["max_temp"].toDouble());
        emit weatherDataChanged();
    });
    connect(m_NetReply.get(), &QNetworkReply::finished, this,
            &CWeatherApi::cleanUp);
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
