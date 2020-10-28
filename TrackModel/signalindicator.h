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
    const QColor GREEN_ON = {30, 200, 30};
    const QColor YELLOW_OFF = {32, 32, 0};
    const QColor YELLOW_ON = {230, 220, 30};
    const QColor RED_OFF = {32, 0, 0};
    const QColor RED_ON = {200, 20, 0};

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QRect redArea(const QRect) const;
    QRect yellowArea(const QRect) const;
    QRect greenArea(const QRect) const;
};

#endif // SIGNALINDICATOR_H
