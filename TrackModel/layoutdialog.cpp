#include "layoutdialog.h"
#include "ui_layoutdialog.h"
#include "trackmodel_main.hpp"

#include <QFileDialog>


// LayoutFileTableModel
LayoutFileTableModel::LayoutFileTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant LayoutFileTableModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
    if( orientation != Qt::Horizontal || role != Qt::DisplayRole ) return QVariant::Invalid;
    if( section == 0 ) return QVariant("Name");
    else if( section == 1 ) return QVariant("File");
    else return QVariant::Invalid;
}

int LayoutFileTableModel::rowCount( const QModelIndex &parent ) const
{
    return TrackModel::routesToLoad.size();
}

int LayoutFileTableModel::columnCount( const QModelIndex &parent ) const
{
    return 2;
}

QVariant LayoutFileTableModel::data( const QModelIndex &index, int role ) const
{
    if( role != Qt::DisplayRole ) return QVariant::Invalid;

    if (!index.isValid()) return QVariant::Invalid;

    using vsize_t = std::vector<TrackModel::RouteFile>::size_type;

    vsize_t row = static_cast<vsize_t>(index.row());
    vsize_t column = static_cast<vsize_t>(index.column());

    if( row < TrackModel::routesToLoad.size() )
    {
        TrackModel::RouteFile &routeRef = TrackModel::routesToLoad[row];
        if( column == 0 ) return QVariant(routeRef.name);
        else if( column == 1 ) return QVariant(routeRef.layoutFile);
    }

    return QVariant::Invalid;
}

void LayoutFileTableModel::signalChange( int idx )
{
    if( idx < 0 ) layoutChanged();
    else dataChanged(index(idx, 0), index(idx, 1));
}


// Layout Dialog
LayoutDialog::LayoutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayoutDialog)
{
    ui->setupUi(this);
    ui->fileTableView->setModel(&fileTable);
    selectedIndex = -1;
}

LayoutDialog::~LayoutDialog()
{
    delete ui;
}

void LayoutDialog::on_buttonBox_accepted()
{
    close();
}

void LayoutDialog::on_fileTableView_clicked(const QModelIndex &index)
{
    selectedIndex = index.row();

    TrackModel::RouteFile &selected = TrackModel::routesToLoad[selectedIndex];
    ui->nameInput->setText(selected.name);
    ui->fileLabel->setText(selected.layoutFile);

    ui->nameInput->setEnabled(true);
    ui->openFileButton->setEnabled(true);
    ui->applyButton->setEnabled(true);
}

void LayoutDialog::on_openFileButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Layout"), QFileInfo().absolutePath(), tr("Layout Files (*.csv)"));
    ui->fileLabel->setText(fileName);
}

void LayoutDialog::on_applyButton_clicked()
{
    TrackModel::routesToLoad[selectedIndex].name = ui->nameInput->text();
    TrackModel::routesToLoad[selectedIndex].layoutFile = ui->fileLabel->text();
    fileTable.signalChange(selectedIndex);
}

void LayoutDialog::on_addButton_clicked()
{
    TrackModel::routesToLoad.push_back(TrackModel::RouteFile("New Route", ""));
    fileTable.signalChange(-1);

    int newIdx = TrackModel::routesToLoad.size() - 1;
    ui->fileTableView->selectRow(newIdx);
    ui->fileTableView->setFocus();
    on_fileTableView_clicked(fileTable.index(newIdx, 0));
}

void LayoutDialog::on_deleteButton_clicked()
{
    if( TrackModel::routesToLoad.size() == 0 ) return;

    int oldIdx = selectedIndex;
    int endIdx = TrackModel::routesToLoad.size() - 1;

    // replace deleted item with last item, then remove last item
    TrackModel::routesToLoad[oldIdx] = TrackModel::routesToLoad[endIdx];
    TrackModel::routesToLoad.pop_back();

    fileTable.signalChange(-1);

    if( TrackModel::routesToLoad.size() > 0 )
    {
        ui->fileTableView->selectRow(0);
        ui->fileTableView->setFocus();
        on_fileTableView_clicked(fileTable.index(0, 0));
    }
    else ui->fileTableView->clearSelection();
}
