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
    Roles[WeatherStateNameRole] = "weatherStateName";
    Roles[WeatherStateAbbrRole] = "weatherStateAbbr";
    Roles[TheTempRole] = "theTemp";
    Roles[MinTempRole] = "minTemp";
    Roles[MaxTempRole] = "maxTemp";
    return Roles;
}

//=============================================================================
bool CWeatherDataModel::setData(int index, const QVariant& value,
                                int role)
{
    return setData(createIndex(index, 0), value, role);
}
