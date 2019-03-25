#include "vpsserwer.h"
#include "ui_vpsserwer.h"

VPSSerwer::VPSSerwer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VPSSerwer)
{
    ui->setupUi(this);
}

VPSSerwer::~VPSSerwer()
{
    delete ui;
}
