/**
 ** This file is part of the "Mobile Weather" project.
 ** Copyright (c) 2020 Florian Meinicke <florian.meinicke@t-online.de>.
 **
 ** Permission is hereby granted, free of charge, to any person obtaining a copy
 ** of this software and associated documentation files (the "Software"), to deal
 ** in the Software without restriction, including without limitation the rights
 ** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 ** copies of the Software, and to permit persons to whom the Software is
 ** furnished to do so, subject to the following conditions:
 **
 ** The above copyright notice and this permission notice shall be included in all
 ** copies or substantial portions of the Software.
 **
 ** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 ** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 ** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 ** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 ** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 ** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 ** SOFTWARE.
 **/

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
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSettings>
#include <QUrlQuery>

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

    m_GeoPosInfoSource.reset(QGeoPositionInfoSource::createDefaultSource(this));

    if (m_GeoPosInfoSource)
    {
        connect(m_GeoPosInfoSource.get(),
                &QGeoPositionInfoSource::positionUpdated, this,
                [this](const auto& update) {
                    setLocationByCoords(update.coordinate());
                });
        // clang-format off
        connect(m_GeoPosInfoSource.get(),
                qOverload<QGeoPositionInfoSource::Error>(
                    &QGeoPositionInfoSource::error),
                this, [this](const auto& /* error */) {
                    qWarning() << "Position source error. Trying to load last "
                                  "location from settings";
                    // clean up insufficient QGeoPositionInfoSource instance
                    m_GeoPosInfoSource->stopUpdates();
                    m_GeoPosInfoSource->deleteLater();
                    m_GeoPosInfoSource.reset();

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
                });
        // clang-format on
        m_GeoPosInfoSource->requestUpdate(2000);
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

    connect(this, &CWeatherApi::locationNameChanged,
            &CWeatherApi::saveLastLocation);
    connect(this, &CWeatherApi::favouriteLocationsChanged,
            &CWeatherApi::saveFavouriteLocations);
}

//=============================================================================
CWeatherApi::~CWeatherApi()
{}

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
    auto Url = QUrl{BASE_URL + "search/"};
    auto Query = QUrlQuery{};
    Query.addQueryItem("query", desiredLocation);
    Url.setQuery(Query);
    m_NetRequest->setUrl(Url);
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
    emit weatherDataRequestStarted();

    m_NetRequest->setUrl({BASE_URL + QString::number(m_LocationWOEID)});
    m_NetReply.reset(m_NetAccessManager->get(*m_NetRequest));

    connect(m_NetReply.get(), &QNetworkReply::readyRead, this,
            &CWeatherApi::onReadyRead);
    connect(this, &CWeatherApi::jsonReady, this, [this]() {
        const auto WeatherDataJsonArray =
            m_ResponseJsonDoc.object().value("consolidated_weather").toArray();

        // clang-format off
        for_each(begin(WeatherDataJsonArray), end(WeatherDataJsonArray),
                 [this, i = 0](const auto& WeatherData) mutable {
                     m_WeatherDataModel->setData(
                         i, WeatherData["applicable_date"].toVariant(),
                         CWeatherDataModel::DateRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["weather_state_name"].toVariant(),
                         CWeatherDataModel::WeatherStateNameRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["weather_state_abbr"].toVariant(),
                         CWeatherDataModel::WeatherStateAbbrRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["the_temp"].toVariant(),
                         CWeatherDataModel::TheTempRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["min_temp"].toVariant(),
                         CWeatherDataModel::MinTempRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["max_temp"].toVariant(),
                         CWeatherDataModel::MaxTempRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["wind_speed"].toVariant(),
                         CWeatherDataModel::WindSpeedRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["wind_direction"].toVariant(),
                         CWeatherDataModel::WindDirectionRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["wind_direction_compass"].toVariant(),
                         CWeatherDataModel::WindDirCompassRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["air_pressure"].toVariant(),
                         CWeatherDataModel::AirPressureRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["humidity"].toVariant(),
                         CWeatherDataModel::HumidityRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["visibility"].toVariant(),
                         CWeatherDataModel::VisibilityRole);
                     m_WeatherDataModel->setData(
                         i, WeatherData["predictability"].toVariant(),
                         CWeatherDataModel::ConfidenceRole);
                     m_WeatherDataModel->setData(
                         i, m_ResponseJsonDoc["sun_rise"].toVariant(),
                         CWeatherDataModel::SunriseTimeRole);
                     m_WeatherDataModel->setData(
                         i, m_ResponseJsonDoc["sun_set"].toVariant(),
                         CWeatherDataModel::SunsetTimeRole);
                     ++i;
                 });
        // clang-format on
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
void CWeatherApi::removeCurrentLocationFromFavourites()
{
    m_FavouriteLocations.remove(m_LocationName);
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
void CWeatherApi::saveLastLocation()
{
    // save last location's weather data
    m_Settings->setValue(LAST_LOCATION_NAME_SETTINGS_KEY, m_LocationName);
    m_Settings->setValue(LAST_LOCATION_WOEID_SETTINGS_KEY, m_LocationWOEID);
}

//=============================================================================
void CWeatherApi::saveFavouriteLocations()
{
    // save favourite locations
    m_Settings->beginGroup(FAVOURITE_LOCATIONS_SETTINGS_GROUP);
    // ensure to delete entries that are no longer present
    m_Settings->remove("");
    foreach (const auto& Key, m_FavouriteLocations.keys())
    {
        m_Settings->setValue(Key, m_FavouriteLocations.value(Key));
    }
    m_Settings->endGroup();
}

//=============================================================================
void CWeatherApi::setLocationName(const QString& locationName)
{
    m_LocationName = locationName;
    emit locationNameChanged();
}

//=============================================================================
void CWeatherApi::setLocationByCoords(const QGeoCoordinate& coordinates)
{
    auto Url = QUrl{BASE_URL + "search/"};
    auto Query = QUrlQuery{};
    const auto Lat = QString::number(coordinates.latitude());
    const auto Long = QString::number(coordinates.longitude());
    Query.addQueryItem("lattlong", Lat + "," + Long);
    Url.setQuery(Query);
    m_NetRequest->setUrl(Url);
    m_NetReply.reset(m_NetAccessManager->get(*m_NetRequest));

    connect(m_NetReply.get(), &QNetworkReply::readyRead, this,
            &CWeatherApi::onReadyRead);
    connect(this, &CWeatherApi::jsonReady, m_GeoPosInfoSource.get(),
            &QGeoPositionInfoSource::stopUpdates);
    connect(m_NetReply.get(), &QNetworkReply::finished, this, [this]() {
        // first clean up before starting a new API request
        cleanUp();
        // the first location is the nearest to the actual current location
        setLocationByIndex(0);
        requestWeatherData();
    });
}
