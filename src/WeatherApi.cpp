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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

using namespace std;

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
    const auto Request = QNetworkRequest{{"https://www.metaweather.com/api/location/44418/"}};
    m_NetReply.reset(m_NetAccessManager->get(Request));

    connect(m_NetReply.get(), &QNetworkReply::finished, this, [this]() {
        qDebug() << m_NetReply->readAll();
        emit dataReady(m_NetReply->readAll().constData());
        // clean up
        m_NetReply->deleteLater();
        m_NetReply = nullptr;
        m_DataBuffer.clear();
    });
}
