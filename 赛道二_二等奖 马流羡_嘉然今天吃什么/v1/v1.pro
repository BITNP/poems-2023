#-------------------------------------------------
#
# Project created by QtCreator 2022-11-20T00:47:31
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = v1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += resources_big

SOURCES += \
        main.cpp \
        start.cpp \
    choose_recipe.cpp \
    enter_recipe.cpp \
    evaluate_recipe.cpp \
    fu.cpp \
    project_feedback.cpp \
    rand.cpp

HEADERS += \
        start.h \
    choose_recipe.h \
    enter_recipe.h \
    evaluate_recipe.h \
    fu.h \
    project_feedback.h \
    rand.h


FORMS += \
        start.ui \
    choose_recipe.ui \
    enter_recipe.ui \
    evaluate_recipe.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    main_jiaran.qrc

RC_FILE += \
    faceicon.rc

