#include "modaldialog.h"
#include "window.h"
#include <QLayout>

using itchio::ModalDialog;

ModalDialog::ModalDialog(Window* const parent) :
QDialog(parent)
{
    setModal(true);
    setObjectName("modalWindow"); // Note: If the object name is changed, remember to update the stylesheet.

//    setWindowFlags(Qt::CustomizeWindowHint |  Qt::FramelessWindowHint | Qt::Dialog);
//    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));
}

void ModalDialog::center()
{
    move(QPoint(0, 0));
}

void ModalDialog::setResizable(const bool resizable)
{
    auto* const l = layout();
    if (l != nullptr)
        l->setSizeConstraint(resizable ? QLayout::SetDefaultConstraint : QLayout::SetFixedSize);
}
