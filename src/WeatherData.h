//============================================================================
/// \file   WeatherData.h
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   18/02/2020
/// \brief  Declaration of the CWeatherData class.
//============================================================================
#ifndef CWEATHERDATA_H
#define CWEATHERDATA_H

//============================================================================
//                                   INCLUDES
//============================================================================
#include <QObject>

/**
 * @brief The CWetherData class encapsulates the weather data (temperature,
 * weather state, wind speed, ...)
 */
class CWeatherData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString weatherStateName MEMBER m_WeatherStateName NOTIFY
                   weatherStateNameChanged)
    Q_PROPERTY(QString weatherStateAbbreviation MEMBER m_WeatherStateAbbreviation
                   NOTIFY weatherStateAbbreviationChanged)
    Q_PROPERTY(qreal theTemp MEMBER m_TheTemp NOTIFY theTempChanged)
    Q_PROPERTY(qreal minTemp MEMBER m_MinTemp NOTIFY minTempChanged)
    Q_PROPERTY(qreal maxTemp MEMBER m_MaxTemp NOTIFY maxTempChanged)

public:
    explicit CWeatherData(QObject* parent = nullptr);

    /**
     * @brief Get the weather state name
     *
     * @return QString The weather state name
     */
    QString weatherStateName() const;

    /**
     * @brief Set the weather state name
     *
     * @param weatherStateName The new weather state name
     */
    void setWeatherStateName(const QString& weatherStateName);

    /**
     * @brief Get the weather state abbreviation
     *
     * @return QString The weather state abbreviation
     */
    QString weatherStateAbbreviation() const;

    /**
     * @brief Set the weather state abbreviation
     *
     * @param weatherStateAbbreviation The new weather state abbreviation
     */
    void setWeatherStateAbbreviation(const QString& weatherStateAbbreviation);

    /**
     * @brief Get the current temperature
     *
     * @return qreal The current temperature
     */
    qreal theTemp() const;

    /**
     * @brief Set the current temperature
     *
     * @param temp The current temperature
     */
    void setTheTemp(const qreal& temp);

    /**
     * @brief Get the minimal temperature of the day
     *
     * @return qreal The minimal temperature
     */
    qreal minTemp() const;

    /**
     * @brief Set the minimal temperature of the day
     *
     * @param temp The minimal temperature
     */
    void setMinTemp(const qreal& temp);

    /**
     * @brief Get the maximal temperature of the day
     *
     * @return qreal The maximal temperature
     */
    qreal maxTemp() const;

    /**
     * @brief Set the maximal temperature of the day
     *
     * @param temp The maximal temperature
     */
    void setMaxTemp(const qreal& temp);

signals:
    /**
     * @brief This signal notifies about changes of the @a m_WeatherStateName
     * member
     */
    void weatherStateNameChanged();

    /**
     * @brief This signal notifies about changes of the
     * @a m_WeatherStateAbbreviation member
     */
    void weatherStateAbbreviationChanged();

    /**
     * @brief This signal notifies about changes of the @a m_TheTemp member
     */
    void theTempChanged();

    /**
     * @brief This signal notifies about changes of the @a m_MinTemp member
     */
    void minTempChanged();

    /**
     * @brief This signal notifies about changes of the @a m_MaxTemp member
     */
    void maxTempChanged();

private:
    QString m_WeatherStateName{};
    QString m_WeatherStateAbbreviation{};
    qreal m_TheTemp{};
    qreal m_MinTemp{};
    qreal m_MaxTemp{};
};

#endif  // CWEATHERDATA_H
