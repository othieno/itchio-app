#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include <QWidget>

#include "appcontroller.h"

namespace Ui
{
class LibraryWidget;
}

class LibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LibraryWidget(QWidget *parent, AppController* controller);
    ~LibraryWidget();


public slots:
    void onMyPurchases(QList<Game> games);

private:
    Ui::LibraryWidget *ui;
    AppController* controller;

    void addGamesTab(const QString& title, QList<Game> games);
};

#endif // LIBRARYWIDGET_H
