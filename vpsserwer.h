#ifndef VPSSERWER_H
#define VPSSERWER_H

#include <QMainWindow>
#include <QTabBar>
#include "parameterschooser.h"
#include "itemsgroup.h"
#include "parallelsystem.h"
#include "serialsystem.h"

namespace Ui {
class VPSSerwer;
}

class VPSSerwer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VPSSerwer(QWidget *parent = nullptr);
    ~VPSSerwer();

private slots:
    void on_addHDD_clicked();

    void on_addPowerSupply_clicked();

    void on_addFirewall_clicked();

    void on_addRouter_clicked();

    void on_addPowerUnit_clicked();

    void on_addCoolingSystem_clicked();

    void on_addSwitch_clicked();

    void on_addConnection_clicked();

private:
    Ui::VPSSerwer *ui;
    ItemsGroup *routers;
    ItemsGroup *switches;
    ItemsGroup *firewalls;
    ItemsGroup *powerSupplies;
    ItemsGroup *powerUnits;
    ItemsGroup *hardDrives;
    ItemsGroup *connections;
    ItemsGroup *coolingSystems;
    SerialSystem *serverSystem;
};

#endif // VPSSERWER_H
