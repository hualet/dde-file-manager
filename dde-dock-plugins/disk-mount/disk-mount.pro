PREFIX = /usr
QT              += core widgets concurrent dbus
TEMPLATE         = lib
CONFIG          += plugin c++11 link_pkgconfig
PKGCONFIG       += dtkwidget gio-2.0

INCLUDEPATH += /usr/include/dde-dock
INCLUDEPATH += $$PWD/../../dde-file-manager-lib/interfaces \
               $$PWD/../../dde-file-manager-lib

TARGET          = $$qtLibraryTarget(dde-disk-mount-plugin)
DESTDIR          = $$_PRO_FILE_PWD_/../
DISTFILES       += disk-mount.json

DEFINES += QT_MESSAGELOGCONTEXT DFM_NO_FILE_WATCHER

#unix: LIBS += -L$$OUT_PWD/../../dde-file-manager-lib -ldde-file-manager

HEADERS += \
    diskmountplugin.h \
    diskcontrolwidget.h \
    diskpluginitem.h \
    diskcontrolitem.h \
    $$PWD/../../dde-file-manager-lib/interfaces/dfmsettings.h \
    $$PWD/../../dde-file-manager-lib/interfaces/dfmstandardpaths.h \
    $$PWD/../../dde-file-manager-lib/interfaces/durl.h \
    dattacheddeviceinterface.h \
    dattachedudisks2device.h \
    dattachedvfsdevice.h

SOURCES += \
    diskmountplugin.cpp \
    diskcontrolwidget.cpp \
    diskpluginitem.cpp \
    diskcontrolitem.cpp \
    $$PWD/../../dde-file-manager-lib/interfaces/dfmsettings.cpp \
    $$PWD/../../dde-file-manager-lib/interfaces/dfmstandardpaths.cpp \
    $$PWD/../../dde-file-manager-lib/interfaces/durl.cpp \
    dattachedudisks2device.cpp \
    dattachedvfsdevice.cpp

target.path = $${PREFIX}/lib/dde-dock/plugins/system-trays/
INSTALLS += target

include($$PWD/udisks2/udisks2.pri)
include($$PWD/../../dde-file-manager-lib/interfaces/vfs/vfs.pri)

RESOURCES += \
    resources.qrc \
    $$PWD/../../dde-file-manager-lib/configure.qrc
