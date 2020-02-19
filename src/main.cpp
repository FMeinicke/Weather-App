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
    // set application name and vendor (for QSettings)
    QCoreApplication::setApplicationName(QStringLiteral("Weather-App"));
    QCoreApplication::setOrganizationName(QStringLiteral("FMeinicke"));

    // auto generated code
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // make C++ class available to QML
    CWeatherApi WeatherApi;
    engine.rootContext()->setContextProperty(QStringLiteral("weatherApi"),
                                             &WeatherApi);

    // auto generated code
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // special handling of the first start of the app
    if (WeatherApi.locationName().isEmpty())
    {
        // app has been started for the first time -> show landing page
        QMetaObject::invokeMethod(engine.rootObjects().first(),
                                  "setFirstStartPage");
    }

    return app.exec();
}
