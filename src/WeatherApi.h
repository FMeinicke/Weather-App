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

public slots:
    /**
     * @brief Request all locations provided by the weather API that are near
     * the @a desiredLocation
     *
     * @param desiredLocation The location that was requested by the user
     */
    void requestLocation(const QString& desiredLocation);

private slots:
    /**
     * @brief Clean up after each call to the weather API
     */
    void cleanUp();

private:
    std::unique_ptr<QNetworkAccessManager> m_NetAccessManager{};
    std::unique_ptr<QNetworkReply> m_NetReply{};
    QByteArray m_DataBuffer{};
};

#endif  // WEATHER_API_H
