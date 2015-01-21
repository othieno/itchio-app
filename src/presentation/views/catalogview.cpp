#include "catalogview.h"

using itchio::CatalogView;

/*!
 * \brief Instantiates a CatalogView that is a child of \a parent.
 */
CatalogView::CatalogView(QWidget& parent, Application& application) :
AbstractView(parent)
{
    ui_.setupUi(this);
    Q_UNUSED(application);
}
/*!
 * \brief Returns the view's caption.
 */
QString CatalogView::caption() const
{
    return "Catalog";
}
