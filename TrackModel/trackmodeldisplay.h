#ifndef TRACKMODELDISPLAY_H
#define TRACKMODELDISPLAY_H

#include <QDialog>

namespace Ui {
class TrackModelDisplay;
}

class TrackModelDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit TrackModelDisplay(QWidget *parent = nullptr);
    ~TrackModelDisplay();

private slots:
    void on_regionComboBox_currentIndexChanged(int index);

private:
    Ui::TrackModelDisplay *ui;
};

#endif // TRACKMODELDISPLAY_H
