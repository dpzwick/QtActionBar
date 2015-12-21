#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QtGlobal>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setApplicationName("ActionBar Demo");
    app.setApplicationDisplayName("ActionBar Demo");

    qDebug("Compiled with Qt version %s",QT_VERSION_STR);
    qDebug("Running with Qt library version %s",qVersion());

    // The following line is needed otherwise translation won't work, see QTBUG-41385
    qDebug("locale=%s",qPrintable(QLocale::system().name()));

    /*
    // Load translation of Qt, maybe needed later.
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    */

    // Load translations for my own code


    QTranslator translator;

    QLocale local = QLocale::system();
    int currentLanguage = local.language();

    translator.load(QString(":/i18n/translations_%1").arg(local.name()));
    app.installTranslator(&translator);

    switch (currentLanguage) {
    case QLocale::Arabic:
        app.setLayoutDirection(Qt::RightToLeft);
        break;
    case QLocale::German:
    case QLocale::English:
    default:
        app.setLayoutDirection(Qt::LeftToRight);
        break;
    }

    MainWindow w;
    w.show();

    return app.exec();
}
