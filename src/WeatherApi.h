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
#include <QByteArray>
#include <QJsonArray>
#include <QObject>
#include <QString>

#include <memory>

//=============================================================================
//                            FORWARD DECLARATIONS
//=============================================================================
class QNetworkAccessManager;
class QNetworkReply;

/**
 * @brief The CWeatherApi class encapsulates all calls to the Weather REST-API
 */
class CWeatherApi : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString locationName MEMBER m_LocationName READ locationName WRITE
                   setLocationName NOTIFY locationNameChanged)
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

    void locationNameChanged();

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

private slots:
    /**
     * @brief Clean up after each call to the weather API
     */
    void cleanUp();

private:
    /**
     * @brief Set the current location's name
     *
     * @param locationName The new name of the current location
     */
    void setLocationName(const QString& locationName);

    std::unique_ptr<QNetworkAccessManager> m_NetAccessManager{};
    std::unique_ptr<QNetworkReply> m_NetReply{};
    QByteArray m_DataBuffer{};  ///< data buffer for the response of the API call
    QJsonArray m_LocationsJsonArray{};  ///< JSON array with possible locations
    int m_LocationWOEID{};  ///< The location's WOEID (Where On Earth ID)
    QString m_LocationName{};
};

#endif  // WEATHER_API_H
