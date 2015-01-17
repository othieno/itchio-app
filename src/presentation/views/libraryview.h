#ifndef LIBRARYVIEW_H
#define LIBRARYVIEW_H

#include "abstractview.h"
#include "ui_libraryview.h"

namespace itchio {

class Window;
class Application;

class LibraryView : public AbstractView
{
    friend class Window;
public:
    QString title() const Q_DECL_OVERRIDE;
private:
    LibraryView(QWidget& parent, Application& application);

    Ui::LibraryView ui_;
//    LibraryDelegate delegate_;
};

} // namespace itchio

#endif // LIBRARYVIEW_H
