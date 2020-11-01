#ifndef SWTRACKCNTRLGUI_H
#define SWTRACKCNTRLGUI_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SWTrackCntrlGUI; }
QT_END_NAMESPACE

class SWTrackCntrlGUI : public QMainWindow
{
    Q_OBJECT

public:
    SWTrackCntrlGUI(QWidget *parent = nullptr);
    ~SWTrackCntrlGUI();
    void setTable();

private:
    Ui::SWTrackCntrlGUI *ui;
};
#endif // SWTRACKCNTRLGUI_H
