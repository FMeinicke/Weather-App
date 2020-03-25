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
    static auto OffsetFromUTC = QDateTime::currentDateTime().offsetFromUtc();
    // Convert the time from UTC to the same time in the local timezone
    // by changing the UTC offset to the current timezone's offset.
    // This means, if the time 07:00 UTC-7 is given and we are currently in the
    // UTC+1 timezone, the time would be displayed as 15:00 UTC+1. To prevent
    // that we change the UTC offset from UTC-7 to UTC+1 (i.e. the given time
    // would now be 07:00 UTC+1; the actual value of the time is not affected).
    // Now the time will be displayed correctly as 07:00.
    // Without this the sunrise time for e.g. Los Angeles would be displayed as
    // 15:00 (if we are in the UTC+1 timezone) when it is actually 07:00 in the
    // local timezone (i.e. UTC-7).
    m_SunriseTime.setOffsetFromUtc(OffsetFromUTC);
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
    static auto OffsetFromUTC = QDateTime::currentDateTime().offsetFromUtc();
    // see above for an explanation
    m_SunsetTime.setOffsetFromUtc(OffsetFromUTC);
    emit sunsetTimeChanged();
}
