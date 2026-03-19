QT = core \
    widgets

CONFIG += c++17

SOURCES += \
        src/calculatorcontroller.cpp \
        src/calculatormodel.cpp \
        src/calculatorview.cpp \
        src/main.cpp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/calculatorcontroller.h \
    src/calculatormodel.h \
    src/calculatorview.h \
