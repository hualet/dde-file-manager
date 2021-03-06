SOURCES += $$PWD/frame.cpp \
    $$PWD/dbus/appearancedaemon_interface.cpp \
    $$PWD/wallpaperlist.cpp \
    $$PWD/wallpaperitem.cpp \
    $$PWD/thumbnailmanager.cpp \
    $$PWD/button.cpp \
    $$PWD/dbus/deepin_wm.cpp

HEADERS  += $$PWD/frame.h \
    $$PWD/dbus/appearancedaemon_interface.h \
    $$PWD/wallpaperlist.h \
    $$PWD/wallpaperitem.h \
    $$PWD/constants.h \
    $$PWD/thumbnailmanager.h \
    $$PWD/button.h \
    $$PWD/dbus/deepin_wm.h

RESOURCES += \
    $$PWD/images.qrc

isEmpty(DISABLE_SCREENSAVER) {
    dbus_screensaver.files = $$PWD/com.deepin.ScreenSaver.xml
    DBUS_INTERFACES += dbus_screensaver
}
