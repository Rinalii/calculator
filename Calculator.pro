QT = core \
    widgets

CONFIG += c++17

SOURCES += \
        calculator.cpp \
        calculatormodel.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    calculator.h \
    calculatormodel.h
