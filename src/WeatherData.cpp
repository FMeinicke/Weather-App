//============================================================================
/// \file   WeatherData.cpp
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   18/02/2020
/// \brief  Implementation of the CWeatherData class.
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherData.h"

static constexpr auto MILES_TO_KM_FACTOR = 1.609344;

//=============================================================================
CWeatherData::CWeatherData(QObject* parent) : QObject(parent)
{}

//=============================================================================
CWeatherData::CWeatherData(const CWeatherData& rhs)
    : m_WeatherStateName{rhs.m_WeatherStateName},
      m_WeatherStateAbbreviation{rhs.m_WeatherStateAbbreviation},
      m_TheTemp{rhs.m_TheTemp},
      m_MinTemp{rhs.m_MinTemp},
      m_MaxTemp{rhs.m_MaxTemp}
{}

//=============================================================================
CWeatherData::CWeatherData(CWeatherData&& rhs) noexcept
    : m_WeatherStateName{rhs.m_WeatherStateName},
      m_WeatherStateAbbreviation{rhs.m_WeatherStateAbbreviation},
      m_TheTemp{rhs.m_TheTemp},
      m_MinTemp{rhs.m_MinTemp},
      m_MaxTemp{rhs.m_MaxTemp}
{}

//=============================================================================
CWeatherData& CWeatherData::operator=(const CWeatherData& rhs)
{
    m_WeatherStateName = rhs.m_WeatherStateName;
    m_WeatherStateAbbreviation = rhs.m_WeatherStateAbbreviation;
    m_TheTemp = rhs.m_TheTemp;
    m_MinTemp = rhs.m_MinTemp;
    m_MaxTemp = rhs.m_MaxTemp;
    return *this;
}

//=============================================================================
CWeatherData& CWeatherData::operator=(CWeatherData&& rhs) noexcept
{
    m_WeatherStateName = rhs.m_WeatherStateName;
    m_WeatherStateAbbreviation = rhs.m_WeatherStateAbbreviation;
    m_TheTemp = rhs.m_TheTemp;
    m_MinTemp = rhs.m_MinTemp;
    m_MaxTemp = rhs.m_MaxTemp;
    return *this;
}

//=============================================================================
QDate CWeatherData::date() const
{
    return m_Date;
}

//=============================================================================
void CWeatherData::setDate(const QDate& day)
{
    m_Date = day;
    emit dateChanged();
}

//=============================================================================
QString CWeatherData::weatherStateName() const
{
    return m_WeatherStateName;
}

//=============================================================================
void CWeatherData::setWeatherStateName(const QString& weatherStateName)
{
    m_WeatherStateName = weatherStateName;
    emit weatherStateNameChanged();
}

//=============================================================================
QString CWeatherData::weatherStateAbbreviation() const
{
    return m_WeatherStateAbbreviation;
}

//=============================================================================
void CWeatherData::setWeatherStateAbbreviation(
    const QString& weatherStateAbbreviation)
{
    m_WeatherStateAbbreviation = weatherStateAbbreviation;
    emit weatherStateAbbreviationChanged();
}

//=============================================================================
qreal CWeatherData::theTemp() const
{
    return m_TheTemp;
}

//=============================================================================
void CWeatherData::setTheTemp(const qreal& temp)
{
    m_TheTemp = temp;
    emit theTempChanged();
}

//=============================================================================
qreal CWeatherData::minTemp() const
{
    return m_MinTemp;
}

//=============================================================================
void CWeatherData::setMinTemp(const qreal& temp)
{
    m_MinTemp = temp;
    emit minTempChanged();
}

//=============================================================================
qreal CWeatherData::maxTemp() const
{
    return m_MaxTemp;
}

//=============================================================================
void CWeatherData::setMaxTemp(const qreal& temp)
{
    m_MaxTemp = temp;
    emit maxTempChanged();
}

//=============================================================================
qreal CWeatherData::windSpeed() const
{
    return m_WindSpeed;
}

//=============================================================================
void CWeatherData::setWindSpeed(const qreal& speed)
{
    m_WindSpeed = speed;
    emit windSpeedChanged();
}

//=============================================================================
void CWeatherData::setWindSpeedInMph(const qreal& speed)
{
    setWindSpeed(speed * MILES_TO_KM_FACTOR);
}

//=============================================================================
qreal CWeatherData::windDirection() const
{
    return m_WindDirection;
}

//=============================================================================
void CWeatherData::setWindDirection(const qreal& dir)
{
    m_WindDirection = dir;
    emit windDirectionChanged();
}

//=============================================================================
QString CWeatherData::windDirCompass() const
{
    return m_WindDirCompass;
}

//=============================================================================
void CWeatherData::setWindDirCompass(const QString& compass)
{
    m_WindDirCompass = compass;
    emit windDirCompassChanged();
}

//=============================================================================
qreal CWeatherData::airPressure() const
{
    return m_AirPressure;
}

//=============================================================================
void CWeatherData::setAirPressure(const qreal& pressure)
{
    m_AirPressure = pressure;
    emit airPressureChanged();
}

//=============================================================================
qreal CWeatherData::humidity() const
{
    return m_Humidity;
}

//=============================================================================
void CWeatherData::setHumidity(const qreal& humidity)
{
    m_Humidity = humidity;
    emit humidityChanged();
}

//=============================================================================
qreal CWeatherData::visibility() const
{
    return m_Visibility;
}

//=============================================================================
void CWeatherData::setVisibility(const qreal& visibility)
{
    m_Visibility = visibility;
    emit visibilityChanged();
}

//=============================================================================
void CWeatherData::setVisibilityInMiles(const qreal& visibility)
{
    setVisibility(visibility * MILES_TO_KM_FACTOR);
}

//=============================================================================
int CWeatherData::confidence() const
{
    return m_Confidence;
}

//=============================================================================
void CWeatherData::setConfidence(int confidence)
{
    m_Confidence = confidence;
    emit confidenceChanged();
}

//=============================================================================
QDateTime CWeatherData::sunriseTime() const
{
    return m_SunriseTime;
}

//=============================================================================
void CWeatherData::setSunriseTime(const QDateTime& time)
{
    m_SunriseTime = time;
    emit sunriseTimeChanged();
}

//=============================================================================
QDateTime CWeatherData::sunsetTime() const
{
    return m_SunsetTime;
}

//=============================================================================
void CWeatherData::setSunsetTime(const QDateTime& time)
{
    m_SunsetTime = time;
    emit sunsetTimeChanged();
}
