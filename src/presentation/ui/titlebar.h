#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>

class QPushButton;
namespace Ui { class Titlebar; }

namespace itchio {

class Titlebar : public QWidget
{
public:
    explicit Titlebar(QWidget& parent);
    ~Titlebar();

    void setTitle(const QString& title);
    void onWindowStateChanged();

    QPushButton* settingsButton() const;

    void showSettingsButton(const bool show = true);
    void showMinimizeButton(const bool show = true);
    void showResizeButtons(const bool show = true);
private:
    QWidget& parent_;

    Ui::Titlebar* const ui_;

    bool showResizeButtons_;
    bool showUnmaximizeButton_;
    bool showMaximizeButton_;
};

} // namespace itchio

#endif // TITLEBAR_H
