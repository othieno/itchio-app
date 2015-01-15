#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

namespace itchio {

class AbstractView : public QWidget
{
public:
    virtual QString title() const = 0;
    virtual bool isResizable() const = 0;
    virtual bool isCentered() const = 0;
protected:
    explicit AbstractView(QWidget* const parent);
};

} // namespace itchio

#endif // ABSTRACTVIEW_H
