#ifndef BINARYINDICATOR_H
#define BINARYINDICATOR_H

#include <QWidget>
#include <QColor>

class BinaryIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit BinaryIndicator(QWidget *parent = nullptr);
    void setValue( bool newVal );

signals:

protected:
    const QColor TRUE_COLOR = {0, 200, 0};
    const QColor FALSE_COLOR = {200, 0, 0};

    bool value;
    void paintEvent(QPaintEvent *event);
};

#endif // BINARYINDICATOR_H
