TEMPLATE = app
QT = gui core
CONFIG += qt \
 debug \
 warn_on \
 console \
 link_pkgconfig \
 --libs \
 --cflags
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui ui/Settings.ui
HEADERS = src/mainwindowimpl.h \
 src/AudioInterface.h \
 src/radioshark.h \
 src/settingsdialog.h \
 src/finnysettings.h
SOURCES = src/mainwindowimpl.cpp \
 src/main.cpp \
 src/AudioInterface.cpp \
 src/radioshark.cpp \
 src/settingsdialog.cpp \
 src/finnysettings.cpp
LIBS = -lhid -lgstinterfaces-0.10 -lgstaudio-0.10 -lgstapp-0.10
RESOURCES += finny.qrc
PKGCONFIG += alsa gstreamer-0.10 gstreamer-plugins-base glib-2.0
