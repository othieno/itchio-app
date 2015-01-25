#ifndef CATALOGVIEW_H
#define CATALOGVIEW_H

#include "abstractview.h"
#include "ui_catalogview.h"

namespace itchio {

class Window;
class Application;

class CatalogView Q_DECL_FINAL : public AbstractView
{
    friend class Window;
private:
    CatalogView(QWidget& parent, Application& application);

    Ui::CatalogView ui_;
//    CatalogDelegate delegate_;
};

} // namespace itchio

#endif // CATALOGVIEW_H
