#include "settingsview.h"
#include "modaldialog.h"

using itchio::SettingsView;

/*!
 * \brief Instantiates a SettingsView that is a child of \a parent.
 */
SettingsView::SettingsView(ModalDialog& parent, Application& application) :
AbstractView(parent)
{
    ui_.setupUi(this);
    Q_UNUSED(application);
}
