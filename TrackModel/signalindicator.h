#ifndef SIGNALINDICATOR_H
#define SIGNALINDICATOR_H

#include <QStyledItemDelegate>

class SignalIndicator : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SignalIndicator(QWidget *parent = nullptr);

signals:

protected:
    const QColor GREEN_OFF = {0, 32, 0};
    const QColor GREEN_ON = {30, 180, 30};
    const QColor YELLOW_OFF = {32, 32, 0};
    const QColor YELLOW_ON = {210, 200, 30};
    const QColor RED_OFF = {32, 0, 0};
    const QColor RED_ON = {180, 10, 0};

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect redArea(const QRect) const;
    QRect yellowArea(const QRect) const;
    QRect greenArea(const QRect) const;
};

#endif // SIGNALINDICATOR_H
