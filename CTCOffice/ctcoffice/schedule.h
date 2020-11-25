#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <QDialog>
#include "mainwindow.h"

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

    std::vector<int> blocks;
    std::vector<std::string> stat;
    std::vector<std::string> t1;
    std::vector<std::string> t2;
    std::vector<std::string> t3;
    std::vector<std::string> t4;
    std::vector<std::string> t5;
    std::vector<std::string> t6;
    std::vector<std::string> t7;
    std::vector<std::string> t8;
    std::vector<std::string> t9;
    std::vector<std::string> t10;

    bool loadComplete;

public slots:
    void on_loadSchedule_clicked();
private slots:


private:
    Ui::schedule *ui;
};

#endif // SCHEDULE_H
