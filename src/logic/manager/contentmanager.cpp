#include "contentmanager.h"
#include "application.h"
#include "window.h"
//#include "views/libraryview.h"
//#include <QDesktopWidget>
#include <QDebug> //TODO Remove me.

static constexpr const int DEFAULT_UPDATE_INTERVAL = 60 * 1000; // 1 minute

using itchio::ContentManager;

ContentManager::ContentManager(Application& application) :
Manager(application)
{}

void ContentManager::showUserContent(const User& user)
{
/*
    closeUserSession();

    currentUser_ = user;
    createUserSession();
*/
    currentUser_ = user;
    qDebug() << "Loading content for user: " << currentUser_.username;
}

void ContentManager::onUserDisconnected()
{
    qDebug() << "Disconnecting user: " << currentUser_.username;
}


#ifdef DEPRECATED
using itchio::Curator;

Curator::Curator(Application& application) :
AbstractController(application),
window_(application.window())
{
    connect(&autoUpdateTimer_, &QTimer::timeout, this, &Curator::refresh);

    autoUpdateTimer_.setInterval(DEFAULT_UPDATE_INTERVAL);
    autoUpdateTimer_.setSingleShot(true);
}

void Curator::onUserAuthenticated(const User& user)
{
    user_ = user;
    refresh();

//    libraryController_.setUser(user);
//    libraryController_.onCreateView();
}

void Curator::refresh()
{
    // If the timer is counting down, then the refresh was requested manually.
    if (autoUpdateTimer_.isActive())
        autoUpdateTimer_.stop();



    qDebug() << "Refreshing..." << user_.username << user_.identifier << user_.key;



//    emit disconnected();

//    if (autoUpdateTimer_.interval() > 0)
//        autoUpdateTimer_.start();
}


void onCreateView()
{
    qDebug("Curator::onCreateView");

/*
    if (libraryView_ == nullptr) {
        libraryView_ = new LibraryView(*this);
    }


    application_.appWindow = new AppWindow(&application_);


    if (libraryView_ == nullptr) {
        libraryView_ = new LibraryView(nullptr, &application_);
    }
//    window_.setView(libraryView_, true);


    auto& window = *application_.appWindow;
    auto& layout = *window.widgetsLayout;

    window.hide();
    window.setupSizeGrip();
    layout.addWidget(libraryView_);
    window.sizeGrip->show();
    window.onWidgetChange(libraryView_);
    window.move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(&window))->rect().center() - window.rect().center());
    window.show();
*/
}

void onDestroyView()
{
    qDebug("Curator::onDestroyView");
/*
    if (libraryView_ != nullptr) {
//        window_.removeView(libraryView_);
        libraryView_->deleteLater();
    }
//    if (libraryView_ != nullptr) {
//        libraryView_->hide();
//        libraryView_->deleteLater();
//    }
*/
}
#endif
