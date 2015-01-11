#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

namespace itchio {

class Application;

class View : public QWidget
{
public:
    enum class Identifier
    {
        None,
        Login,
        LoginPrompt,
        Content
    };

    const View::Identifier& identifier() const;
    QString title() const;

    virtual bool isResizable() const = 0;
    virtual bool isCentered() const = 0;

protected:
    View(const View::Identifier& identifier, QWidget* const parent);

private:
    View::Identifier identifier_;
};

} // namespace itchio

#endif // ABSTRACTVIEW_H
