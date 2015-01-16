TEMPLATE = app
TARGET = itchio

INCLUDEPATH += \
    src \
    src/logic \
    src/logic/domain \
    src/logic/manager \
    src/persistence \
    src/persistence/dao \
    src/presentation \
    src/presentation/controllers \
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
    src/persistence/databasemanager.h \
    src/persistence/dao/abstractdao.h \
    src/persistence/dao/gamedao.h \
    src/presentation/window.h \
    src/presentation/controllers/abstractcontroller.h \
    src/persistence/database.h \
    src/presentation/views/abstractview.h \
    src/presentation/views/contentview.h \
    src/presentation/views/authenticationview.h \
    src/presentation/modaldialog.h

SOURCES += \
    src/itchio.cpp \
    src/logic/application.cpp \
    src/logic/authenticator.cpp \
    src/logic/settings.cpp \
    src/persistence/databasemanager.cpp \
    src/presentation/window.cpp \
    src/logic/domain/game.cpp \
    src/logic/domain/library.cpp \
    src/logic/domain/purchase.cpp \
    src/logic/domain/user.cpp \
    src/logic/manager/contentmanager.cpp \
    src/logic/manager/networkmanager.cpp \
    src/persistence/dao/gamedao.cpp \
    src/presentation/controllers/abstractcontroller.cpp \
    src/logic/manager/manager.cpp \
    src/persistence/database.cpp \
    src/presentation/views/abstractview.cpp \
    src/presentation/views/contentview.cpp \
    src/presentation/views/authenticationview.cpp \
    src/presentation/modaldialog.cpp

FORMS += \
    src/presentation/forms/appwindow.ui \
    src/presentation/forms/librarywidget.ui \
    src/presentation/forms/loginwidget.ui \
    src/presentation/forms/modalwindow.ui \
    src/presentation/forms/secondarywindow.ui \
    src/presentation/forms/settingswidget.ui \
    src/presentation/forms/loginprompt.ui \
    src/presentation/forms/content.ui \
    src/presentation/forms/window.ui

include(itchio.pri)
