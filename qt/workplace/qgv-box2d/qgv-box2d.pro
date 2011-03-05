SOURCES += main.cpp
INCLUDEPATH += /opt/Box2D/include
LIBS +=-L/opt/Box2D/lib -lBox2D
QMAKE_LFLAGS_DEBUG+=-Wl,-rpath,/opt/Box2D/lib
