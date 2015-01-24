#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "abstractview.h"
#include "ui_libraryview.h"
#include <QSqlQueryModel>
#include <QTimer>

namespace itchio {

class Window;
class Application;
class ContentManager;

class LibraryView : public AbstractView
{
    friend class Window;
public:
    enum class Filter
    {
        All,
        Purchases
    };

    void setFilter(const Filter& filter);
    const Filter& filter() const;
private:
    LibraryView(QWidget& parent, Application& application);

    QSqlQuery filterQuery(const Filter& filter) const;

    Ui::LibraryView ui_;
    ContentManager& contentManager_;
    QSqlQueryModel model_;
    Filter filter_;
    QModelIndex selectedIndex_;
    QTimer delayTimer_;

    constexpr static int DELAY_TIMER_INTERVAL = 350;
private slots:
    void onItemSelected(const QModelIndex& index);
    void onUpdateDetailedView();
    void onLibraryUpdated();
};

} // namespace itchio

#endif // LIBRARYVIEW_H
