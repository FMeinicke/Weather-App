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

#include <QObject>

/**
 * @brief The CWeatherApi class encapsulates all calls to the Weather REST-API
 */
class CWeatherApi : public QObject
{
    Q_OBJECT
public:
    explicit CWeatherApi(QObject* parent = nullptr);

signals:
};

#endif  // WEATHER_API_H
