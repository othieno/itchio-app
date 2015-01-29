#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "abstractview.h"
#include "ui_libraryview.h"
#include "librarymodel.h"
#include <QSqlQueryModel>
#include <QTimer>

namespace itchio {

class Window;
class Application;
class Content;
class ContentManager;

class LibraryView Q_DECL_FINAL : public AbstractView
{
    friend class Window;
private:
    LibraryView(QWidget& parent, Application& application);

    static QString createSubtitleString(const Content& content);

    Ui::LibraryView ui_;
    LibraryModel model_;

    QModelIndex selectedIndex_;
    QTimer delayTimer_;

    constexpr static int DELAY_TIMER_INTERVAL = 350;
    /*!
     * \brief Cover image resolution.
     */
    constexpr static unsigned COVER_IMAGE_WIDTH  = 315;
    constexpr static unsigned COVER_IMAGE_HEIGHT = 250;
private slots:
    void onItemSelected(const QModelIndex& index);
    void onUpdateDetails();
    void onLibraryUpdated();
};

} // namespace itchio

#endif // LIBRARYVIEW_H
