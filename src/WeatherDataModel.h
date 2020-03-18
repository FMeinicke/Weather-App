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
        DateRole = Qt::UserRole + 1,
        WeatherStateNameRole,
        WeatherStateAbbrRole,
        TheTempRole,
        MinTempRole,
        MaxTempRole,
        WindSpeedRole,
        WindDirectionRole,
        WindDirCompassRole,
        AirPressureRole,
        HumidityRole,
        VisibilityRole,
        ConfidenceRole,
        SunriseTimeRole,
        SunsetTimeRole,
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
    /**
     * @brief Fills @ m_WeatherStateTranslations map with all possible weather
     * state names so that they can be properly translated later on.
     */
    void setupWeatherStateTranslations();

    /**
     * @brief Similar to Qt's @a tr function. Translates the weather state names
     * from the API by looking thm up in the @a m_WeatherStateTranslations member
     *
     * @param s The weather state name to translate
     * @return QString The translated version of the weather state name
     */
    QString weatherTr(const QString& s) const;

private:
    // clang-format off
    static constexpr size_t m_NumDays{6}; ///< for how many days weather data is available

    QList<CWeatherData> m_WeatherDataList{};
    QMap<QString, QString> m_WeatherStateTranslations{}; ///< holds translations from english to the currently active language
    // clang-format on
};

#endif  // CWEATHERDATAMODEL_H
