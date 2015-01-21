#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

namespace itchio {

class AbstractView : public QWidget
{
public:
    QString title() const;
    virtual QString caption() const = 0;

    virtual bool isResizable() const;
    virtual bool isCentered() const;
protected:
    explicit AbstractView(QWidget& parent);
};

} // namespace itchio

#endif // ABSTRACTVIEW_H
