#ifndef SETTINGSVIEW_H
#define SETTINGSVIEW_H

#include "abstractview.h"
#include "ui_settingsview.h"

namespace itchio {

class ModalDialog;
class Application;

class SettingsView Q_DECL_FINAL : public AbstractView
{
    friend class ModalDialog;
private:
    SettingsView(ModalDialog& dialog, Application& application);

    Ui::SettingsView ui_;
//    SettingsDelegate delegate_;
};

} // namespace itchio

#endif // SETTINGSVIEW_H
