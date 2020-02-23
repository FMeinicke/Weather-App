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
#include <QDate>
#include <QObject>
#include <QString>

/**
 * @brief The CWetherData class encapsulates the weather data (temperature,
 * weather state, wind speed, ...)
 */
class CWeatherData : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QDate date MEMBER m_Date NOTIFY dateChanged)
    Q_PROPERTY(QString weatherStateName MEMBER m_WeatherStateName NOTIFY
                   weatherStateNameChanged)
    Q_PROPERTY(QString weatherStateAbbreviation MEMBER m_WeatherStateAbbreviation
                   NOTIFY weatherStateAbbreviationChanged)
    Q_PROPERTY(qreal theTemp MEMBER m_TheTemp NOTIFY theTempChanged)
    Q_PROPERTY(qreal minTemp MEMBER m_MinTemp NOTIFY minTempChanged)
    Q_PROPERTY(qreal maxTemp MEMBER m_MaxTemp NOTIFY maxTempChanged)
    Q_PROPERTY(qreal windSpeed MEMBER m_WindSpeed NOTIFY windSpeedChanged)
    Q_PROPERTY(
        qreal windDirection MEMBER m_WindDirection NOTIFY windDirectionChanged)
    Q_PROPERTY(
        QString windDirCompass MEMBER m_WindDirCompass NOTIFY windDirCompassChanged)
    Q_PROPERTY(qreal airPressure MEMBER m_AirPressure NOTIFY airPressureChanged)
    Q_PROPERTY(qreal humidity MEMBER m_Humidity NOTIFY humidityChanged)
    Q_PROPERTY(qreal visibility MEMBER m_Visibility NOTIFY visibilityChanged)
    Q_PROPERTY(qreal confidence MEMBER m_Confidence NOTIFY confidenceChanged)
    Q_PROPERTY(
        QDateTime sunriseTime MEMBER m_SunriseTime NOTIFY sunriseTimeChanged)
    Q_PROPERTY(QDateTime sunsetTime MEMBER m_SunsetTime NOTIFY sunsetTimeChanged)

public:
    explicit CWeatherData(QObject* parent = nullptr);

    /**
     * @brief Copy c'tor
     */
    CWeatherData(const CWeatherData& rhs);

    /**
     * @brief Move c'tor
     */
    CWeatherData(CWeatherData&& rhs) noexcept;

    /**
     * @brief Copy assignment operator
     */
    CWeatherData& operator=(const CWeatherData& rhs);

    /**
     * @brief Move assignment operator
     */
    CWeatherData& operator=(CWeatherData&& rhs) noexcept;

    /**
     * @brief D'tor
     */
    ~CWeatherData() override = default;

    /**
     * @brief Get the date this weather data applies to
     *
     * @return QDate The date
     */
    QDate date() const;

    /**
     * @brief Set the date for this weather data
     *
     * @param weatherStateName The new date
     */
    void setDate(const QDate& date);

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

    /**
     * @brief Get the wind speed
     *
     * @return qreal The wind speed in mph
     */
    qreal windSpeed() const;

    /**
     * @brief Set the wind speed
     *
     * @param speed The new wind speed in mph
     */
    void setWindSpeed(const qreal& speed);

    /**
     * @brief Get the wind direction
     *
     * @return qreal The wind direction in degrees
     */
    qreal windDirection() const;

    /**
     * @brief Set the wind direction
     *
     * @param dir The new wind direction in mph
     */
    void setWindDirection(const qreal& dir);

    /**
     * @brief Get the compass point of the wind direction (e.g. N for north wind)
     *
     * @return QString The compass point of the wind direction
     */
    QString windDirCompass() const;

    /**
     * @brief Set the compass point of the wind direction (e.g. N for north wind)
     *
     * @param compass The new compass point of the wind direction
     */
    void setWindDirCompass(const QString& compass);

    /**
     * @brief Get the current air pressure
     *
     * @return qreal The air pressure in mbar
     */
    qreal airPressure() const;

    /**
     * @brief Set the air pressure
     *
     * @param pressure The new air pressure in mbar
     */
    void setAirPressure(const qreal& pressure);

    /**
     * @brief Get the current humidity
     *
     * @return qreal The humidity in percent (0 - 100)
     */
    qreal humidity() const;

    /**
     * @brief Set the humidity
     *
     * @param qreal The new humidity in percent (0 - 100)
     */
    void setHumidity(const qreal& humidity);

    /**
     * @brief Get the current visibility
     *
     * @return qreal The visibility in miles
     */
    qreal visibility() const;

    /**
     * @brief Set the visibility
     *
     * @param qreal The new visibility in miles
     */
    void setVisibility(const qreal& visibility);

    /**
     * @brief Get the current confidence
     *
     * @return qreal The confidence in percent (0 - 100)
     */
    int confidence() const;

    /**
     * @brief Set the confidence
     *
     * @param qreal The new confidence in percent (0 - 100)
     */
    void setConfidence(int confidence);

    /**
     * @brief Get the time of sunrise for this day
     *
     * @return qreal The time of sunrise
     */
    QDateTime sunriseTime() const;

    /**
     * @brief Set the time of sunrise for this day
     *
     * @param qreal The new time of sunrise
     */
    void setSunriseTime(const QDateTime& time);

    /**
     * @brief Get the time of sunset for this day
     *
     * @return qreal The time of sunset
     */
    QDateTime sunsetTime() const;

    /**
     * @brief Set the time of sunset for this day
     *
     * @param qreal The new time of sunset
     */
    void setSunsetTime(const QDateTime& time);

signals:
    /**
     * @brief This signal notifies about changes of the @a m_Date member
     */
    void dateChanged();

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

    /**
     * @brief This signal notifies about changes of the @a m_WindSpeed member
     */
    void windSpeedChanged();

    /**
     * @brief This signal notifies about changes of the @a m_WindDirection member
     */
    void windDirectionChanged();

    /**
     * @brief This signal notifies about changes of the @a m_WindDirCompass member
     */
    void windDirCompassChanged();

    /**
     * @brief This signal notifies about changes of the @a m_AirPressure member
     */
    void airPressureChanged();

    /**
     * @brief This signal notifies about changes of the @a m_Humidity member
     */
    void humidityChanged();

    /**
     * @brief This signal notifies about changes of the @a m_Visibility member
     */
    void visibilityChanged();

    /**
     * @brief This signal notifies about changes of the @a m_Confidence member
     */
    void confidenceChanged();

    /**
     * @brief This signal notifies about changes of the @a m_SunriseTime member
     */
    void sunriseTimeChanged();

    /**
     * @brief This signal notifies about changes of the @a m_SunsetTime member
     */
    void sunsetTimeChanged();

private:
    QDate m_Date{};  ///< the date this data applies to
    QString m_WeatherStateName{};  ///< name of the current weather state (e.g. clear)
    QString m_WeatherStateAbbreviation{};  ///< abbreviation of the weather state (for icons)
    qreal m_TheTemp{};                 ///< the current temperature in °C
    qreal m_MinTemp{};           ///< the minimum temperature in °C for the day
    qreal m_MaxTemp{};           ///< the maximum temperature in °C for the day
    qreal m_WindSpeed{};         ///< wind speed in mph
    qreal m_WindDirection{};     ///< direction of the wind in degrees
    QString m_WindDirCompass{};  ///< compass point of the wind direction
    qreal m_AirPressure{};       ///< air pressure in mbar
    qreal m_Humidity{};          ///< humidity in percent
    qreal m_Visibility{};        ///< visibility in miles
    int m_Confidence{};          ///< confidence of the forecast in percent
    QDateTime m_SunriseTime{};   ///< time of sunrise
    QDateTime m_SunsetTime{};    ///< time of sunset
};

#endif  // CWEATHERDATA_H
