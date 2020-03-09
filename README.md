# Mobile Weather
A simple weather app in C++ and QML demonstrating how to talk to REST APIs with Qt

## Getting Started
Um die App selbst zu bauen, muss das Projekt rekursiv geklont werden, damit die `android_openssl` Abhängigkeit ebenfalls mit geklont wird:
```shell
git clone --recursive https://github.com/FMeinicke/Weather-App.git
```

Wenn das Projekt als zip-Ordner heruntergeladen wird, muss `android_openssl` manuell auch noch heruntergeladen werden. Dazu muss einfach das zip-Archiv von https://github.com/KDAB/android_openssl.git heruntergeladen werden. Das Archiv muss in den Ordner `Weather-App/third_party/android_openssl/` entpackt werden. Das Projekt sollte am Ende die folgende Struktur besitzen, damit es erfolgreich kompiliert werden kann:
```
Weather-App/
|-- android/
|-- res
|-- src/
|-- third_party/
|   `-- android_openssl/
|       |-- openssl.pri
|       |-- arm/
|       |-- arm64/
|       `-- ...
`-- Weather-App.pro
```

Dann kann die `Weather-App.pro` Datei einfach in QtCreator geöffnet und kompiliert werden.

## Aufbau der App
- Aufteilung von Logik (C++) und GUI (QML)
### C++
- zentrale `CWeatherApi` Klasse
  - macht alle Anfragen an die REST API von MetaWeather.com
- empfangene Wetter-Daten werden in Objekt der `CWeatherData` Klasse gespeichert
- für QML werden diese Daten über die `CWeatherDataModel` Klasse als Model bereitgestellt
- Verwendung von `QSettings` zum persistenten Speichern von Daten über die Laufzeit der App hinaus
  - speichert den letzten ausgewählten und favorisierte Orte
  - diese werden beim nächsten App-Start wieder geladen und die Wetter-Daten des letzten Orts automatisch abgefragt und angezeigt

### QML
- bei ersten Start der App wird HomeForm.ui.qml gezeigt
- über das Such-Icon kann jederzeit die SearchPageForm.qml aufgerufen und ein Ort gesucht werden
- nach Auswahl des Ortes werden die Wetter-Daten für die nächsten 5 Tage angezeigt
- der aktuelle Ort kann als Favorit gespeichert werden
- die Favoriten können über den Drawer ausgewählt werden, um schnell deren Wetter-Daten anzuzeigen

## Aufgetretene Probleme
### Fehlende (oder nicht auffindbare) OpenSSL Libraries auf Android
#### Problem:
- ohne Weiteres konnte nicht mit HTTPS APIs kommuniziert werden; 
- folgender Fehler trat dabei auf:
    ```
    qt.network.ssl: QSslSocket::connectToHostEncrypted: TLS initialization failed
    ```

#### Lösung:
- die benötigten OpenSSL Libraries müssen manuell mit der App ausgeliefert werden (d.h. `ANDROID_EXTRA_LIBS` in der .pro Datei hinzufügen)
- KDAB stellt dafür die nötigen Libraries und eine .pri Datei bereit, die einfach in das eigene Projekt eingebunden werden kann (s. https://github.com/KDAB/android_openssl):

    ```qmake
    include(third_party/android_openssl/openssl.pri)
    ```

### Falsche Schriftart auf OnePlus Smartphone
#### Problem:
- auf OnePlus Smartphones wird die Default-Einstellung der Schriftart ignoriert (s. https://bugreports.qt.io/browse/QTBUG-69494)

#### Lösung/Workaround:
- der zu verwendende Font muss mit der App mitgeliefert werden (m.H. Qt's Resource System)
- dann kann in der main.cpp dieser Font geladen und als globaler Font gesetzt werden
```cpp
    QGuiApplication app(argc, argv);
    const auto id = QFontDatabase::addApplicationFont(":/fonts/Roboto/Roboto-Regular.ttf");
    const auto family = QFontDatabase::applicationFontFamilies(id).at(0);
    app.setFont({family, 16});
```
