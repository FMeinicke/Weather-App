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

#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>

int main(int argc, char* argv[])
{
    // set application name and vendor (for QSettings)
    QCoreApplication::setApplicationName(QStringLiteral("Weather-App"));
    QCoreApplication::setOrganizationName(QStringLiteral("FMeinicke"));

    // auto generated code
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // translation
    QTranslator Translator;
    if (Translator.load(QLocale(), QCoreApplication::applicationName(),
                        QStringLiteral("_"), QStringLiteral(":/translations")))
    {
        app.installTranslator(&Translator);
    }
    else
    {
        qWarning()
            << "Could not load translation for" << QLocale::system().name();
    }

    // set app font - work around for QTBUG-69494
    const auto id =
        QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Regular.ttf");
    const auto family = QFontDatabase::applicationFontFamilies(id).at(0);
    app.setFont({family, 16});

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

    return app.exec();
}
