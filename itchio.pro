TEMPLATE = app
TARGET = itchio

INCLUDEPATH += \
    src \
    src/logic \
    src/logic/domain \
    src/logic/manager \
    src/persistence \
    src/persistence/dao \
    src/presentation/controllers \
    src/presentation/models \
    src/presentation/ui \
    src/presentation/views

HEADERS += \
    src/logic/application.h \
    src/logic/authenticator.h \
    src/logic/settings.h \
    src/logic/domain/game.h \
    src/logic/domain/library.h \
    src/logic/domain/price.h \
    src/logic/domain/purchase.h \
    src/logic/domain/user.h \
    src/logic/manager/contentmanager.h \
    src/logic/manager/networkmanager.h \
    src/logic/manager/manager.h \
    src/persistence/database.h \
    src/persistence/databasemanager.h \
    src/persistence/dao/abstractdao.h \
    src/persistence/dao/gamedao.h \
    src/presentation/controllers/abstractcontroller.h \
    src/presentation/models/librarymodel.h \
    src/presentation/ui/modaldialog.h \
    src/presentation/ui/titlebar.h \
    src/presentation/ui/window.h \
    src/presentation/views/abstractview.h \
    src/presentation/views/authenticationview.h \
    src/presentation/views/catalogview.h \
    src/presentation/views/libraryview.h \
    src/presentation/views/settingsview.h \
    src/logic/domain/content.h \
    src/presentation/ui/framelesswindow.h \
    src/logic/manager/sessionmanager.h

SOURCES += \
    src/itchio.cpp \
    src/logic/application.cpp \
    src/logic/authenticator.cpp \
    src/logic/settings.cpp \
    src/logic/domain/game.cpp \
    src/logic/domain/library.cpp \
    src/logic/domain/purchase.cpp \
    src/logic/domain/user.cpp \
    src/logic/manager/contentmanager.cpp \
    src/logic/manager/networkmanager.cpp \
    src/logic/manager/manager.cpp \
    src/persistence/database.cpp \
    src/persistence/databasemanager.cpp \
    src/persistence/dao/gamedao.cpp \
    src/presentation/controllers/abstractcontroller.cpp \
    src/presentation/views/abstractview.cpp \
    src/presentation/views/authenticationview.cpp \
    src/presentation/views/catalogview.cpp \
    src/presentation/views/libraryview.cpp \
    src/presentation/views/settingsview.cpp \
    src/presentation/models/librarymodel.cpp \
    src/presentation/ui/modaldialog.cpp \
    src/presentation/ui/titlebar.cpp \
    src/presentation/ui/window.cpp \
    src/logic/domain/content.cpp \
    src/logic/domain/price.cpp \
    src/logic/manager/sessionmanager.cpp

FORMS += \
    src/presentation/forms/authenticationview.ui \
    src/presentation/forms/catalogview.ui \
    src/presentation/forms/libraryview.ui \
    src/presentation/forms/modaldialog.ui \
    src/presentation/forms/settingsview.ui \
    src/presentation/forms/titlebar.ui \
    src/presentation/forms/window.ui

RESOURCES += \
    res/resources.qrc

include(itchio.pri)
