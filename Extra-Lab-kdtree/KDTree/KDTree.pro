macx {
  cache()
}

TEMPLATE = app

CONFIG -= qt
CONFIG -= app_bundle

SOURCES = $$files($$PWD/*.cpp)
HEADERS = $$files($$PWD/*.h)

QMAKE_CXXFLAGS += -std=c++11 -Wreturn-type
