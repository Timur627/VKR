QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 static

# Добавление флага для статической сборки
CONFIG += static

# Для статической сборки Qt, необходимо указать путь к статической версии Qt.
# Убедитесь, что ваша версия Qt собрана со статическими флагами.
# Вставьте путь к каталогу статической сборки Qt (если необходимо).
# QMAKE_LIBS += -L/path/to/static/qt/libs

SOURCES += \
    fileselector.cpp \
    getmodel.cpp \
    main.cpp \
    modelselection.cpp \
    processingmodels.cpp \
    savepage.cpp \
    settingspage.cpp \
    writemodel.cpp

HEADERS += \
    fileselector.h \
    getmodel.h \
    globals.h \
    modelselection.h \
    processingmodels.h \
    savepage.h \
    settingspage.h \
    writemodel.h

FORMS +=

# Стандартные правила для развертывания.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
