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
     * @brief This signal is emitted whe the requested data is ready (i.e. has
     * been received from the API)
     *
     * @param data The data that was received
     */
    void dataReady(QString mydata);

public slots:
    /**
     * @brief Request new data by issueing a call to the weather API.
     */
    void requestData();

private:
    std::unique_ptr<QNetworkAccessManager> m_NetAccessManager{};
    std::unique_ptr<QNetworkReply> m_NetReply{};
    QByteArray m_DataBuffer{};
};

#endif  // WEATHER_API_H
