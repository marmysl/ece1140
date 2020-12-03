#ifndef FILES_H
#define FILES_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {class Files;}
QT_END_NAMESPACE

class Files : public QDialog
{
    Q_OBJECT

public:
    explicit Files(QWidget *parent = nullptr);
    ~Files();
    void mapDisplay();

private:
    Ui::Files *ui;
};

#endif // FILES_H
