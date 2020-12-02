#ifndef THROUGHPUT_H
#define THROUGHPUT_H

#include <QDialog>
#include "../../TrackModel/station_tracking.h"

namespace Ui {
class throughput;
}

class throughput : public QDialog
{
    Q_OBJECT

public:
    explicit throughput(QWidget *parent = nullptr);
    ~throughput();

    int timerID;
    int passNum;
    std::string line;

private:
    Ui::throughput *ui;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // THROUGHPUT_H
