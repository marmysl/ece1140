#include "schedule.h"
#include "ui_schedule.h"
#include <QFileDialog>
#include <QDebug>
#include <QTableWidget>

#include <fstream>
#include <iostream>

#include "mainwindow.h"

schedule::schedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::schedule)
{
    ui->setupUi(this);
}

schedule::~schedule()
{
    delete ui;
}

void schedule::on_loadSchedule_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Schedule"), QFileInfo().absolutePath(), tr("Schedule Files (*.csv)"));
    ui->fileLabel->setText(fileName);
    scheduleParser(fileName.toStdString());
}

void schedule::scheduleParser(std::string fileName){
    using namespace TrackModel;

    std::ifstream scheduleFile;

    QFileInfo lfInfo(QString::fromStdString(fileName));
    scheduleFile.open(lfInfo.absoluteFilePath().toStdString(), std::ios::in);

    if( !scheduleFile.is_open() ) throw std::invalid_argument ("Unable to open schedule");

    std::string nextLine;
    std::stringstream buf = std::stringstream ();

    enum ParseState {
        LL_BLOCK, LL_STATION, LL_TRAIN_1, LL_TRAIN_2, LL_TRAIN_3, LL_TRAIN_4, LL_TRAIN_5,
        LL_TRAIN_6, LL_TRAIN_7, LL_TRAIN_8, LL_TRAIN_9, LL_TRAIN_10,
    };

    const char *stateNames[] {
        "Block", "Station", "Train 1", "Train 2", "Train 3", "Train 4", "Train 5",
        "Train 6", "Train 7", "Train 8", "Train 9", "Train 10"
    };

    //CREATE VARIABLES
    ParseState state;
    int fileLine = 1;

    int blocknum;
    std::string station;
    std::string train1;
    std::string train2;
    std::string train3;
    std::string train4;
    std::string train5;
    std::string train6;
    std::string train7;
    std::string train8;
    std::string train9;
    std::string train10;

    // for each line of the config file
    while( getline(scheduleFile, nextLine) ) {

        loadComplete = false;
        // check if line is commented
        if( (nextLine.length() == 0) || (nextLine.at(0) == '#') )
        {
            fileLine += 1;
            continue;
        }

        state = LL_BLOCK;
        auto iter = nextLine.begin();

        while( iter != nextLine.end() ) {
            // while we still have tokens to read
            char nextChar = *iter;

            if( nextChar == ',' ) {
                // delimiter read, advance to next state
                std::string bufStr = buf.str();

                try {
                    switch( state ) {
                        case LL_BLOCK:
                            blocknum = parseIntStrict(bufStr);
                            break;

                        case LL_STATION:
                            station = bufStr;
                            break;

                        case LL_TRAIN_1:
                            train1 = bufStr;
                            break;

                        case LL_TRAIN_2:
                            train2 = bufStr;
                            break;

                        case LL_TRAIN_3:
                            train3 = bufStr;
                            break;

                        case LL_TRAIN_4:
                            train4 = bufStr;
                            break;

                        case LL_TRAIN_5:
                            train5 = bufStr;
                            break;

                        case LL_TRAIN_6:
                            train6 = bufStr;
                            break;

                        case LL_TRAIN_7:
                            train7 = bufStr;
                            break;

                        case LL_TRAIN_8:
                            train8 = bufStr;
                            break;

                        case LL_TRAIN_9:
                            train9 = bufStr;
                            break;

                        case LL_TRAIN_10:
                            train10 = bufStr;
                            break;
                    }
                }
                catch( const std::invalid_argument &e ) {
                    buf.str(std::string());
                    buf.clear();
                    buf << "Error parsing " << stateNames[state] << " (col " << (state + 1) << ") on line " << fileLine;
                    buf << ": " << e.what();
                    scheduleFile.close();
                    throw LayoutParseError(buf.str());
                }
                catch( const std::out_of_range &e ) {
                    buf.str(std::string());
                    buf.clear();
                    buf << "Error parsing field " << stateNames[state] << " on line " << fileLine;
                    buf << ": " << e.what();
                    scheduleFile.close();
                    throw LayoutParseError(buf.str());
                }
                catch( const LayoutParseError &e )
                {
                    scheduleFile.close();
                    throw e;
                }

                state = static_cast<ParseState>(state + 1);
                buf.str(std::string());
                buf.clear();
            }
            else {
                // Non-delimiter char, append to buf
                buf.put(nextChar);
            }

            // advance to next char of line
            iter++;
        }

        if( state == LL_TRAIN_10 ) {
            train10 = buf.str();
            buf.str(std::string());
            buf.clear();
        }
        else {
            buf.str(std::string());
            buf.clear();
            buf << "Too few fields on line " << fileLine;
            scheduleFile.close();
            throw LayoutParseError(buf.str());
        }

        setSchedule(fileLine, blocknum, station, train1, train2,
                             train3, train4, train5, train6,
                             train7, train8, train9, train10);

        // proceed to next line
        fileLine += 1;
    }
    // end while

    scheduleFile.close();
    loadComplete = true;

    for(int i = 0; i < blocks.size(); i++){
        qDebug() << "Block: " << QString::number(blocks.at(i));
        qDebug() << "Station: " << QString::fromStdString(stat.at(i));

        qDebug() << "Train 1: " << QString::fromStdString(t1.at(i));
        qDebug() << "Train 2: " << QString::fromStdString(t2.at(i));
        qDebug() << "Train 3: " << QString::fromStdString(t3.at(i));
        qDebug() << "Train 4: " << QString::fromStdString(t4.at(i));
        qDebug() << "Train 5: " << QString::fromStdString(t5.at(i));
        qDebug() << "Train 6: " << QString::fromStdString(t6.at(i));
        qDebug() << "Train 7: " << QString::fromStdString(t7.at(i));
        qDebug() << "Train 8: " << QString::fromStdString(t8.at(i));
        qDebug() << "Train 9: " << QString::fromStdString(t9.at(i));
        qDebug() << "Train 10: " << QString::fromStdString(t10.at(i));
    }

    setScheduleTable();
}

int schedule::parseIntStrict(std::string str) {
    size_t lenParsed;
    int result = std::stoi(str, &lenParsed);

    if( lenParsed != str.length() ) throw std::invalid_argument(str + " is not a valid integer value");
    return result;
}

void schedule::setSchedule(int linenum, int blocknum, std::string station, std::string train1, std::string train2,
                 std::string train3, std::string train4, std::string train5, std::string train6, std::string train7,
                 std::string train8, std::string train9, std::string train10){

    blocks.push_back(blocknum);
    stat.push_back(station);
    t1.push_back(train1);
    t2.push_back(train2);
    t3.push_back(train3);
    t4.push_back(train4);
    t5.push_back(train5);
    t6.push_back(train6);
    t7.push_back(train7);
    t8.push_back(train8);
    t9.push_back(train9);
    t10.push_back(train10);

    if(blocks.size() != linenum-1){
        qDebug() << "you done screwed up";
    }
}

void schedule::setScheduleTable(){
    ui->scheduleTable->setColumnCount(12);
    ui->scheduleTable->setRowCount(18);
    QStringList htitle;
    htitle << "Block" << "Station" << "Train 1 Arrival Time" << "Train 2 Arrival Time" << "Train 3 Arrival Time"
           <<  "Train 4 Arrival Time" <<  "Train 5 Arrival Time" << "Train 6 Arrival Time" << "Train 7 Arrival Time" <<
                "Train 8 Arrival Time" << "Train 9 Arrival Time" << "Train 10 Arrival Time";
    ui->scheduleTable->setHorizontalHeaderLabels(htitle);

    //inserting a row
    //ui->scheduleTable->insertRow(ui->scheduleTable->rowCount());
    for(int i = 0; i < blocks.size(); i++){
        ui->scheduleTable->setItem(i, 0, new QTableWidgetItem(QString::number(blocks.at(i))));
        ui->scheduleTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(stat.at(i))));
        ui->scheduleTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(t1.at(i))));
        ui->scheduleTable->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(t2.at(i))));
        ui->scheduleTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(t3.at(i))));
        ui->scheduleTable->setItem(i, 5, new QTableWidgetItem(QString::fromStdString(t4.at(i))));
        ui->scheduleTable->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(t5.at(i))));
        ui->scheduleTable->setItem(i, 7, new QTableWidgetItem(QString::fromStdString(t6.at(i))));
        ui->scheduleTable->setItem(i, 8, new QTableWidgetItem(QString::fromStdString(t7.at(i))));
        ui->scheduleTable->setItem(i, 9, new QTableWidgetItem(QString::fromStdString(t8.at(i))));
        ui->scheduleTable->setItem(i, 10, new QTableWidgetItem(QString::fromStdString(t9.at(i))));
        ui->scheduleTable->setItem(i, 11, new QTableWidgetItem(QString::fromStdString(t10.at(i))));
    }
}
