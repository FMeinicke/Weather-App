//============================================================================
/// \file   WeatherDataModel.h
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   18/02/2020
/// \brief  Declaration of the CWeatherDataModel class.
//============================================================================
#ifndef CWEATHERDATAMODEL_H
#define CWEATHERDATAMODEL_H

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherData.h"

#include <QAbstractListModel>
#include <QList>

/**
 * @brief The CWetherDataModel class exposes CWeatherData objects for different
 * days using Qt's MVC approach
 */
class CWeatherDataModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /**
     * @brief The eWeatherDataRoles enum defines the different roles
     * of this model. Each role represents an attribute of the underlying data
     * (i.e. the attributes of the CWeatherData class in this case) that
     * should be accessible from QML.
     */
    enum eWeatherDataRoles
    {
        WeatherStateNameRole = Qt::UserRole + 1,
        WeatherStateAbbrRole,
        TheTempRole,
        MinTempRole,
        MaxTempRole,
    };

    explicit CWeatherDataModel(QObject* parent = nullptr);

    /**
     * @reimp
     * @brief Get the data (i.e. the weather data like temperature, weather state,
     * wind, ..., depending on @a role) at the given index @a index.
     */
    QVariant data(const QModelIndex& index, int role) const override;

    /**
     * @reimp
     * @brief Set the data for the given role @a role to @a value at the given
     * index @a index.
     */
    bool setData(const QModelIndex& index, const QVariant& value,
                 int role = Qt::EditRole) override;

    /**
     * @reimp
     * @brief Get the number of items (i.e. days of weather data) of this model.
     */
    int rowCount(const QModelIndex& /*parent*/ = QModelIndex()) const override;

    /**
     * @reimp
     * @brief Get the model's role names
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Convenience function that creates a QModelIndex from @a index and
     * then calls the other overload of @a setData
     */
    bool setData(int index, const QVariant& value, int role = Qt::EditRole);

private:
    static constexpr size_t m_NumDays{1}; ///< for how many days weather data is available

    QList<CWeatherData> m_WeatherDataList{};
};

#endif  // CWEATHERDATAMODEL_H