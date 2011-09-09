#-------------------------------------------------
#
# Project created by luxin
# update 2011-09-5 T17:31:28
#
#-------------------------------------------------


QT       += core gui opengl
TEMPLATE = app


LIBS     += -L ./ -lgpscene
TARGET = tank

SOURCES += main.cpp\
        tankview.cpp \
    tank.cpp \
    game.cpp \
    tankgnu.cpp \
    abstractaction.cpp \
    spark.cpp \
    fps.cpp \
    combatbase.cpp

HEADERS  += tankview.h \
    tank.h \
    game.h \
    tankgnu.h \
    abstractaction.h \
    sprite.h \
    spark.h \
    fps.h \
    global.h \
    mapbase.h \
    mapmanager.h \
    mapinfo.h \
    mapitem.h \
    combatbase.h

DEPLOYMENTFOLDERS = # file1 dir1

symbian:TARGET.UID3 = 0xE0891BF6

# Smart Installer package's UID
# This UID is from the protected range
# and therefore the package will fail to install if self-signed
# By default qmake uses the unprotected range value if unprotected UID is defined for the application
# and 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
#symbian:TARGET.CAPABILITY += NetworkServices

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

RESOURCES += \
    image.qrc

OTHER_FILES += \
    tank2.png \
    tank1.png \
    start_game.png \
    logo.png \
    contniue_game.png \
    base1.png

