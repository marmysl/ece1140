#ifndef LAYOUTDIALOG_H
#define LAYOUTDIALOG_H

#include <QDialog>
#include <QAbstractTableModel>

namespace Ui {
class LayoutDialog;
}

class LayoutFileTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LayoutFileTableModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void signalChange( int idx );
};


class LayoutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LayoutDialog(QWidget *parent = nullptr);
    ~LayoutDialog();

private slots:
    void on_buttonBox_accepted();
    void on_fileTableView_clicked(const QModelIndex &index);
    void on_openFileButton_clicked();
    void on_addButton_clicked();
    void on_deleteButton_clicked();
    void on_nameInput_textEdited(const QString &arg1);

private:
    Ui::LayoutDialog *ui;
    LayoutFileTableModel fileTable;
    int selectedIndex;
};

#endif // LAYOUTDIALOG_H
