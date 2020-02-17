//============================================================================
/// \file   main.cpp
/// \author Florian Meinicke <florian.meinicke@t-online.de>
/// \date   06/02/2020
/// \brief  A mobile app that displays the weather forecast from a public
/// REST-API
//============================================================================

//============================================================================
//                                   INCLUDES
//============================================================================
#include "WeatherApi.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    // auto generated code
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // make C++ class available to QML
    qmlRegisterSingletonType<CWeatherApi>(
        "WeatherApi.Types", 1, 0, "WeatherApi",
        [](QQmlEngine* /*engine*/, QJSEngine * /*scriptEngine*/) -> QObject* {
            auto WeatherApi = new CWeatherApi();
            return WeatherApi;
        });

    return app.exec();
}
