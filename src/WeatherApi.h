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
/// \file   WeatherApi.h
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   07/02/2020
/// \brief  Declaration of the CWeatherApi class.
//============================================================================
#ifndef WEATHER_API_H
#define WEATHER_API_H

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherDataModel.h"

#include <QByteArray>
#include <QJsonDocument>
#include <QMap>
#include <QObject>
#include <QQmlListProperty>
#include <QString>

#include <memory>

//=============================================================================
//                            FORWARD DECLARATIONS
//=============================================================================
class QGeoCoordinate;
class QGeoPositionInfoSource;
class QNetworkAccessManager;
class QNetworkReply;
class QNetworkRequest;
class QSettings;

/**
 * @brief The CWeatherApi class encapsulates all calls to the Weather REST-API
 */
class CWeatherApi : public QObject
{
    Q_OBJECT

    Q_PROPERTY(
        QString locationName MEMBER m_LocationName NOTIFY locationNameChanged)
    Q_PROPERTY(CWeatherDataModel* weatherDataModel READ weatherDataModel NOTIFY
                   weatherDataModelChanged)
    Q_PROPERTY(QStringList favouriteLocations READ favouriteLocations NOTIFY
                   favouriteLocationsChanged)
public:
    /**
     * @brief Construct a new CWeatherApi object
     *
     * @param parent The parent object
     */
    explicit CWeatherApi(QObject* parent = nullptr);

    /**
     * @brief Destroy the CWeatherApi object
     */
    ~CWeatherApi() override;

    /**
     * @brief Get the current location's name
     *
     * @return QString The current location's name
     */
    QString locationName() const;

    /**
     * @brief Get the weather data model corresponding to the current location
     *
     * @return CWeatherDataModel* A pointer to the weather data model for the
     * current location
     */
    CWeatherDataModel* weatherDataModel() const;

    /**
     * @brief Get all favourite locations
     *
     * @return QStringList A list of the favourite location names
     */
    QStringList favouriteLocations();

signals:
    /**
     * @brief This signal is emitted when the requested location was retrieved
     * from the API. In case there was no matching location (i.e. the API does not
     * provide weather data about the requested location) then @a locations will
     * be empty.
     *
     * @param locations A list of all locations matching the request given in
     * @a requestLocation. Empty if there was no match.
     */
    void locationsReady(QStringList locations);

    /**
     * @brief This signal notifies about changes in the @a m_LocationName member.
     */
    void locationNameChanged();

    /**
     * @internal
     * @brief This signal is emitted every time the internal JSON doc has been
     * created from the raw JSON data and is now ready to be processed further.
     */
    void jsonReady();

    /**
     * @brief Ths signal is emitted every time the @a requestWeatherData slot is
     * called. This can be used to provide a visual feedback to the user that the
     * probably long running API request is running.
     */
    void weatherDataRequestStarted();

    /**
     * @brief This signal notifies about changes in the @a m_WeatherDataModel
     * member
     */
    void weatherDataModelChanged();

    /**
     * @brief This signal notifies about changes in the @a m_FavouriteLocations
     * member
     */
    void favouriteLocationsChanged();

public slots:
    /**
     * @brief Request all locations provided by the weather API that are near
     * the @a desiredLocation
     *
     * @param desiredLocation The location that was requested by the user
     */
    void requestLocation(const QString& desiredLocation);

    /**
     * @brief Set the location that should be used for all further API calls and
     * is identified by the index @a index with respect to the current list of
     * possible locations.
     *
     * @param index The index of the location with respect to the current list of
     * possible locations
     */
    void setLocationByIndex(int index);

    /**
     * @brief Set the location that should be used for all further API calls and
     * is identified by the name @a name with respect to the list of favourite
     * locations.
     *
     * @param name The name of the location with respect to the list of favourite
     * locations
     */
    void setLocationByName(const QString& name);

    /**
     * @brief Request weather data about the currently selected location
     */
    void requestWeatherData();

    /**
     * @brief Adds the current location to the list of favourite locations
     */
    void addCurrentLocationToFavourites();

    /**
     * @brief Removes the current location from the list of favourite locations
     */
    void removeCurrentLocationFromFavourites();

private slots:
    /**
     * @brief Reads the data from the network reply into the internal buffer and
     * constructs a JSON document from the data. This JSON doc is saved in the @a
     * m_ResponseJsonDoc member. Emits @a jsonReady indcating that the JSON doc
     * has been successfully constructed and can be processed further.
     */
    void onReadyRead();

    /**
     * @brief Clean up after each call to the weather API
     */
    void cleanUp();

    /**
     * @brief Permanently saves the current location as last location so that it
     * can be restored when the app is closed and re-opened.
     */
    void saveLastLocation();

    /**
     * @brief Permanently saves the current list of favourite locations so that
     * they are available when the app is opened the next time.
     */
    void saveFavouriteLocations();

private:
    /**
     * @brief Set the current location's name
     *
     * @param locationName The new name of the current location
     */
    void setLocationName(const QString& locationName);

    /**
     * @brief Set the location that should be used for all further API calls and
     * is identified by the coordinates @a coordinates.
     *
     * @param coordinates The coordinates of the current location
     */
    void setLocationByCoords(const QGeoCoordinate& coordinate);

    // clang-format off
    std::unique_ptr<QNetworkAccessManager> m_NetAccessManager{};
    std::unique_ptr<QNetworkReply> m_NetReply{};
    std::unique_ptr<QNetworkRequest> m_NetRequest{};
    QByteArray m_DataBuffer{};  ///< data buffer for the response of the API call
    QJsonDocument m_ResponseJsonDoc{};  ///< JSON doc with the API reponse
    int m_LocationWOEID{};  ///< The location's WOEID (Where On Earth ID)
    QString m_LocationName{};
    std::unique_ptr<CWeatherDataModel> m_WeatherDataModel{};  ///< all the weather data
    std::unique_ptr<QSettings> m_Settings{};
    QMap<QString, int> m_FavouriteLocations{};  ///< map location names to WOEID's of fav locations
    std::unique_ptr<QGeoPositionInfoSource> m_GeoPosInfoSource{};  ///< for retrieving the curret GPS location
    // clang-format on
};

#endif  // WEATHER_API_H
