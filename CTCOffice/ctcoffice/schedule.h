#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <QDialog>

namespace Ui {
class schedule;
}

class schedule : public QDialog
{
    Q_OBJECT

public:
    explicit schedule(QWidget *parent = nullptr);
    ~schedule();
    void scheduleParser(std::string);
    static int parseIntStrict(std::string);
    void setSchedule(int, int, std::string, std::string, std::string,
                     std::string, std::string, std::string, std::string,
                     std::string, std::string, std::string, std::string);
    void setScheduleTable();

    std::vector<int> blocks;
    std::vector<std::string> stat;
    std::vector<QTime> t1;
    std::vector<QTime> t2;
    std::vector<QTime> t3;
    std::vector<QTime> t4;
    std::vector<QTime> t5;
    std::vector<QTime> t6;
    std::vector<QTime> t7;
    std::vector<QTime> t8;
    std::vector<QTime> t9;
    std::vector<QTime> t10;

    std::vector<std::string> tv1;
    std::vector<std::string> tv2;
    std::vector<std::string> tv3;
    std::vector<std::string> tv4;
    std::vector<std::string> tv5;
    std::vector<std::string> tv6;
    std::vector<std::string> tv7;
    std::vector<std::string> tv8;
    std::vector<std::string> tv9;
    std::vector<std::string> tv10;

    bool loadComplete;

public slots:
    void on_loadSchedule_clicked();
private slots:


private:
    Ui::schedule *ui;
};

#endif // SCHEDULE_H
