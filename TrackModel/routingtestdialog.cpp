#include "routingtestdialog.h"
#include "ui_routingtestdialog.h"
#include "trackrouter.h"

RoutingTestDialog::RoutingTestDialog(TrackModel::Route *route, QWidget *parent) :
    QDialog(parent),
    route(route), ui(new Ui::RoutingTestDialog)
{
    ui->setupUi(this);
    blockList = new int[route->blocks.size()];

    int i = 0;
    for( auto &kvp : route->blocks )
    {
        blockList[i] = kvp.first;
        ui->fromCombo->addItem(QString::number(kvp.first));
        ui->toCombo->addItem(QString::number(kvp.first));
        i++;
    }

    router = new TrackModel::TrackRouter(route);
}

RoutingTestDialog::~RoutingTestDialog()
{
    delete router;
    delete blockList;
    delete ui;
}

void RoutingTestDialog::on_buttonBox_accepted()
{
    int fromBlk = blockList[ui->fromCombo->currentIndex()];
    int toBlk = blockList[ui->toCombo->currentIndex()];

    using namespace TrackModel;

    TrainPathInfo path = router->findPath(fromBlk, BLK_NODIR, toBlk);

    std::stringstream buf;
    for( Block *blk : path.blocks )
    {
        buf << blk->id;
        buf << " > ";
    }

    ui->resultLabel->setText(QString::fromStdString(buf.str()));
}

void RoutingTestDialog::on_buttonBox_rejected()
{
    close();
}
