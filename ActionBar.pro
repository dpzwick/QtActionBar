QT += core gui widgets

TARGET = ActionBar

TEMPLATE = app

SOURCES += src/main.cpp \
    src/mainwindow.cpp  \
    src/actionbar.cpp \
    src/menustyle.cpp

HEADERS  += src/mainwindow.h  \
    src/actionbar.h \
    src/menustyle.h

FORMS +=

RC_FILE = resources/myapp.rc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += doc/html/* \
    resources/i18n/*  \
    resources/icons/* \
    android/AndroidManifest.xml \
    resources/myapp.rc

RESOURCES += resources/icons.qrc resources/i18n.qrc

TRANSLATIONS =  \
    resources/i18n/translations_ar.ts \
    resources/i18n/translations_en.ts \
    resources/i18n/translations_de.ts

