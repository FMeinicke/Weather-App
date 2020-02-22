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
