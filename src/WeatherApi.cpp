//============================================================================
/// \file   WeatherApi.cpp
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   07/02/2020
/// \brief  Implementation of the CWeatherApi class.
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherApi.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace std;

static const auto BASE_URL =
    QStringLiteral("https://www.metaweather.com/api/location/");

//=============================================================================
CWeatherApi::CWeatherApi(QObject* parent)
    : QObject{parent},
      m_NetAccessManager{make_unique<QNetworkAccessManager>(this)},
      m_NetReply{nullptr}
{}

//=============================================================================
CWeatherApi::~CWeatherApi() = default;

//=============================================================================
void CWeatherApi::requestData()
{
    qDebug() << "Hello World";
    const auto Request =
        QNetworkRequest{{"https://www.metaweather.com/api/location/44418/"}};
    m_NetReply.reset(m_NetAccessManager->get(Request));

    connect(m_NetReply.get(), &QNetworkReply::readyRead, this, [this]() {
        m_DataBuffer = m_NetReply->readAll();
        emit dataReady(m_DataBuffer);
    });
    connect(m_NetReply.get(), &QNetworkReply::finished, this,
            &CWeatherApi::cleanUp);
}

//=============================================================================
void CWeatherApi::requestLocation(const QString& desiredLocation)
{
    const auto Request =
        QNetworkRequest{BASE_URL + "search/?query=" + desiredLocation};
    m_NetReply.reset(m_NetAccessManager->get(Request));

    connect(m_NetReply.get(), &QNetworkReply::readyRead, this, [this]() {
        m_DataBuffer = m_NetReply->readAll();
        QJsonParseError Error;
        const auto ResponseJsonDoc =
            QJsonDocument::fromJson(m_DataBuffer, &Error);
        if (ResponseJsonDoc.isNull())
        {
            qWarning() << "Could not parse received JSON data! The following "
                          "error occured:"
                       << Error.errorString();
        }

        const auto LocationsJsonArray = ResponseJsonDoc.array();

        auto Locations = QStringList();
        for_each(begin(LocationsJsonArray), end(LocationsJsonArray),
                 [&Locations](const QJsonValue& val) {
                     const auto Location = val.toObject();
                     Locations.append(Location["title"].toString());
                  });
        emit locationsReady(Locations);
    });
    connect(m_NetReply.get(), &QNetworkReply::finished, this,
            &CWeatherApi::cleanUp);
}

//=============================================================================
void CWeatherApi::cleanUp()
{
    m_NetReply->deleteLater();
    m_NetReply = nullptr;
    m_DataBuffer.clear();
}
