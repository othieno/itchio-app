#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

namespace itchio {

template<class UserInterface, class Layout, class Controller>
class AbstractView : public QWidget
{
    Q_STATIC_ASSERT_X(std::is_default_constructible<UserInterface>::value, "UserInterface requires a default constructor.");
public:
    void setResizable(const bool resizable = true);
protected:
    AbstractView(Controller& controller, QWidget& parent);
    virtual ~AbstractView();

    QString fullViewTitle(QString shortTitle) const;

    UserInterface* const ui_;
    Controller& controller_;
};

template<class UI, class Layout, class C>
AbstractView<UI, Layout, C>::AbstractView(C& controller, QWidget& parent) :
ui_(new UI),
controller_(controller)
{
    Q_ASSERT(ui_ != nullptr);
    ui_->setupUi(this);

    // Delete the parent's previous layout and replace it with a new one containing only this view.
    auto* const oldLayout = parent.layout();
    if (oldLayout != nullptr)
        delete oldLayout;

    auto* const newLayout = new Layout;
    newLayout->addWidget(this);
    parent.setLayout(newLayout);
}

template<class UI, class L, class C>
AbstractView<UI, L, C>::~AbstractView()
{
    delete ui_;
}

template<class UI, class L, class C>
QString AbstractView<UI, L, C>::fullViewTitle(QString title) const
{
    return controller_.applicationName().append(title.prepend(" - "));
}

} // namespace itchio

#endif // ABSTRACTVIEW_H
