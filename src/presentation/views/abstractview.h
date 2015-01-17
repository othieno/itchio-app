#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

namespace itchio {

class AbstractView : public QWidget
{
public:
    virtual QString title() const = 0;
    virtual bool isResizable() const;
    virtual bool isCentered() const;
protected:
    explicit AbstractView(QWidget* const parent);
};

} // namespace itchio

#endif // ABSTRACTVIEW_H
