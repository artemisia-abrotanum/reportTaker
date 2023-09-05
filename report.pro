QT       += core gui

QT += printsupport

QT += core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    $$PWD/makereports.h \

SOURCES += \
    $$PWD/makereports.cpp \
    main.cpp


FORMS += \
    makereports.ui

RESOURCES += \
    cat.png



win32 {
PWD_WIN = $${PWD}
DESTDIR_WIN = $${OUT_PWD}
PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

copyfiles.commands = $$quote(cmd /C xcopy /y /c $${PWD_WIN}\\cat.png $${DESTDIR_WIN}\\)
 }
 macx {
 copyfiles.commands = $$quote(cp $$PWD/cat.png $$OUT_PWD/../)
}
linux {
copyfiles.commands = $$quote(cp $$PWD/cat.png $$OUT_PWD/../)

}


# Default rules for deployment.

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


include(reportMaker.pri)
QMAKE_EXTRA_TARGETS +=  copyfiles
POST_TARGETDEPS += copyfiles
