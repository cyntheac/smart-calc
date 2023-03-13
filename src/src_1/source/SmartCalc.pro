QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    backend.c \
    check_input.c \
    polish_notation.c \
    calculate.c \
    stack_num.c \
    stack_op.c \
	main.cpp \
    mainwindow.cpp \
	qcustomplot.cpp

HEADERS += \
    mainwindow.h \
	backend.h \
	qcustomplot.h

FORMS += \
    mainwindow.ui

RESOURCES += \
	haha.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target