//============================================================================
/// \file   WeatherDataModel.cpp
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   21/02/2020
/// \brief  Implementation of the CWeatherDataModel class.
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherDataModel.h"

#include <QDebug>

//=============================================================================
CWeatherDataModel::CWeatherDataModel(QObject* parent) : QAbstractListModel(parent)
{
    for (size_t i = 0; i < m_NumDays; i++)
    {
        m_WeatherDataList.append(CWeatherData{this});
    }
}

//============================================================================
QVariant CWeatherDataModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case DateRole:
        return m_WeatherDataList[index.row()].date();
    case WeatherStateNameRole:
        return m_WeatherDataList[index.row()].weatherStateName();
    case WeatherStateAbbrRole:
        return m_WeatherDataList[index.row()].weatherStateAbbreviation();
    case TheTempRole:
        return m_WeatherDataList[index.row()].theTemp();
    case MinTempRole:
        return m_WeatherDataList[index.row()].minTemp();
    case MaxTempRole:
        return m_WeatherDataList[index.row()].maxTemp();
    case WindSpeedRole:
        return m_WeatherDataList[index.row()].windSpeed();
    case WindDirectionRole:
        return m_WeatherDataList[index.row()].windDirection();
    case WindDirCompassRole:
        return m_WeatherDataList[index.row()].windDirCompass();
    case AirPressureRole:
        return m_WeatherDataList[index.row()].airPressure();
    case HumidityRole:
        return m_WeatherDataList[index.row()].humidity();
    case VisibilityRole:
        return m_WeatherDataList[index.row()].visibility();
    case ConfidenceRole:
        return m_WeatherDataList[index.row()].confidence();
    case SunriseTimeRole:
        return m_WeatherDataList[index.row()].sunriseTime();
    case SunsetTimeRole:
        return m_WeatherDataList[index.row()].sunsetTime();
    default:
        qWarning() << "Unknown role" << role << "for CWeatherDataModel::data";
        return QVariant();
    }
}

//=============================================================================
bool CWeatherDataModel::setData(const QModelIndex& index, const QVariant& value,
                                int role)
{
    switch (role)
    {
    case DateRole:
        m_WeatherDataList[index.row()].setDate(value.toDate());
        break;
    case WeatherStateNameRole:
        m_WeatherDataList[index.row()].setWeatherStateName(value.toString());
        break;
    case WeatherStateAbbrRole:
        m_WeatherDataList[index.row()].setWeatherStateAbbreviation(
            value.toString());
        break;
    case TheTempRole:
        m_WeatherDataList[index.row()].setTheTemp(value.toDouble());
        break;
    case MinTempRole:
        m_WeatherDataList[index.row()].setMinTemp(value.toDouble());
        break;
    case MaxTempRole:
        m_WeatherDataList[index.row()].setMaxTemp(value.toDouble());
        break;
    case WindSpeedRole:
        m_WeatherDataList[index.row()].setWindSpeed(value.toDouble());
        break;
    case WindDirectionRole:
        m_WeatherDataList[index.row()].setWindDirection(value.toDouble());
        break;
    case WindDirCompassRole:
        m_WeatherDataList[index.row()].setWindDirCompass(value.toString());
        break;
    case AirPressureRole:
        m_WeatherDataList[index.row()].setAirPressure(value.toDouble());
        break;
    case HumidityRole:
        m_WeatherDataList[index.row()].setHumidity(value.toDouble());
        break;
    case VisibilityRole:
        m_WeatherDataList[index.row()].setVisibility(value.toDouble());
        break;
    case ConfidenceRole:
        m_WeatherDataList[index.row()].setConfidence(value.toInt());
        break;
    case SunriseTimeRole:
        m_WeatherDataList[index.row()].setSunriseTime(value.toDateTime());
        break;
    case SunsetTimeRole:
        m_WeatherDataList[index.row()].setSunsetTime(value.toDateTime());
        break;
    default:
        qWarning() << "Unknown role" << role << "for CWeatherDataModel::setData";
        return false;
    }

    emit dataChanged(index, index, {role});
    return true;
}

//============================================================================
int CWeatherDataModel::rowCount(const QModelIndex& /*parent*/) const
{
    return m_WeatherDataList.size();
}

//============================================================================
QHash<int, QByteArray> CWeatherDataModel::roleNames() const
{
    QHash<int, QByteArray> Roles;
    Roles[DateRole] = "date";
    Roles[WeatherStateNameRole] = "weatherStateName";
    Roles[WeatherStateAbbrRole] = "weatherStateAbbr";
    Roles[TheTempRole] = "theTemp";
    Roles[MinTempRole] = "minTemp";
    Roles[MaxTempRole] = "maxTemp";
    Roles[WindSpeedRole] = "windSpeed";
    Roles[WindDirectionRole] = "windDirection";
    Roles[WindDirCompassRole] = "windDirCompass";
    Roles[AirPressureRole] = "airPressure";
    Roles[HumidityRole] = "humidity";
    Roles[VisibilityRole] = "visibility";
    Roles[ConfidenceRole] = "confidence";
    Roles[SunriseTimeRole] = "sunriseTime";
    Roles[SunsetTimeRole] = "sunsetTime";
    return Roles;
}

//=============================================================================
bool CWeatherDataModel::setData(int index, const QVariant& value,
                                int role)
{
    return setData(createIndex(index, 0), value, role);
}
