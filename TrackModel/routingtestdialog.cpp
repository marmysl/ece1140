#include "routingtestdialog.h"
#include "ui_routingtestdialog.h"
#include "trackrouter.h"

RoutingTestDialog::RoutingTestDialog(TrackModel::Route *route, QWidget *parent) :
    QDialog(parent),
    route(route), ui(new Ui::RoutingTestDialog)
{
    ui->setupUi(this);
    int nBlk = route->blocks.size();
    blockList = new int[nBlk];

    int i = 0;
    for( auto &kvp : route->blocks )
    {
        blockList[i] = kvp.first;
        i++;
    }

    std::sort(blockList, blockList + nBlk);

    for( i = 0; i < nBlk; i++ )
    {
        ui->fromCombo->addItem(QString::number(blockList[i]));
        ui->toCombo->addItem(QString::number(blockList[i]));
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
    bool first = true;

    for( Block *blk : path.blocks )
    {
        if( !first ) buf << " > ";
        first = false;

        buf << blk->id;
    }

    ui->routeLabel->setText(QString::fromStdString(buf.str()));

    if( path.switchStates.size() > 0 )
    {
        buf.str(std::string());
        first = true;

        for( auto &sw : path.switchStates )
        {
            if( !first ) buf << ", ";
            first = false;

            buf << '{' << sw.first << ": ";
            buf << ((sw.second == SW_DIVERGING) ? "Diverge}" : "Straight}");
        }

        ui->switchesLabel->setText(QString::fromStdString(buf.str()));
    }
    else
    {
        ui->switchesLabel->setText("N/A");
    }
}

void RoutingTestDialog::on_buttonBox_rejected()
{
    close();
}
