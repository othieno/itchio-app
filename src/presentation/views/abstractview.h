#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

namespace itchio {

class AbstractView : public QWidget
{
public:
    QString fullWindowTitle() const;

    virtual bool isResizable() const;
    virtual bool isCentered() const;
protected:
    explicit AbstractView(QWidget& parent);

    void paintEvent(QPaintEvent* const event) Q_DECL_OVERRIDE;
};

} // namespace itchio

#endif // ABSTRACTVIEW_H
