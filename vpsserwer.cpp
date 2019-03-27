#include "vpsserwer.h"
#include "ui_vpsserwer.h"


VPSSerwer::VPSSerwer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VPSSerwer)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
    hardDrives = new ItemsGroup();
    routers = new ItemsGroup();
    switches = new ItemsGroup();
    powerSupplies = new ItemsGroup();
    powerUnits = new ItemsGroup();
    coolingSystems = new ItemsGroup();
    connections = new ItemsGroup();
    firewalls = new ItemsGroup();

    hardDrives->addItem(new Item("IBM Lenovo 800GB 3,5 SSD", "HARD_DRIVES", 1005287.0, 1.3));
    hardDrives->addItem(new Item("Western Digital Ultrastar DC HC520 1200GB HDD", "HARD_DRIVES", 2001193.0, 1.6));
    hardDrives->addItem(new Item("Dell R530 1800GB 3,5 HDD", "HARD_DRIVES", 1600021.0, 1.0));
    hardDrives->addItem(new Item("Seagate Skyhawk 3,5 HDD", "HARD_DRIVES", 1032480.0, 1.2));
    hardDrives->addItem(new Item("Intel DC S3700 400GB SSD", "HARD_DRIVES", 5061480.0, 2.0));

    routers->addItem(new Item("Cisco 2901-SEC/K9", "ROUTERS", 400000.0, 2.0));
    routers->addItem(new Item("Cisco C819G-4G-GA/K9", "ROUTERS", 770242.0, 2.6));
    routers->addItem(new Item("Cisco ISR4331/K9", "ROUTERS", 1550508.0, 2.5));

    powerSupplies->addItem(new Item("Fogo 59kW 74 KVA FDG 80 IS", "POWER_SUPPLIES", 1300046.0, 72.0));
    powerSupplies->addItem(new Item("Fogo 80 PD 81 KVA 65 KW", "POWER_SUPPLIES", 1568650.0, 70.0));
    powerSupplies->addItem(new Item("AN-S3/65 z ATS 50kW", "POWER_SUPPLIES", 1968254.0, 38.0));

    powerUnits->addItem(new Item("Barracuda 14kW 17KVA ATS/SZR", "POWER_ITEMS", 1970462.0, 48.0));
    powerUnits->addItem(new Item("Barracuda 16kW 20KVA ATS/SZR", "POWER_UNITS", 1579044.0, 21.0));

    switches->addItem(new Item("Cisco N7L-C7018","SWITCHES", 412076.0, 1.2));
    switches->addItem(new Item("Cisco SG200-50-K9-EU","SWITCHES", 475220.0, 1.0));
    switches->addItem(new Item("Cisco N7K-C7009","SWITCHES", 637144.0, 1.6));
    switches->addItem(new Item("Cisco N7K-C7010", "SWITCHES", 529104.0, 2.2));
    switches->addItem(new Item("Cisco N5K-C5548P-Fa", "SWITCHES", 196670.0, 1.6));
    switches->addItem(new Item("Cisco N5K-C5548UP-FA", "SWITCHES", 196670.0, 2.1));
    switches->addItem(new Item("Cisco N4K-40001L-XPX", "SWITCHES", 374530, 1.8));

    firewalls->addItem(new Item("Huawei Secospace USG6390", "FIREWALLS", 410232.0, 2.3));
    firewalls->addItem(new Item("Huawei Secospace USG6320", "FIREWALLS", 333930.0, 2.2));
    firewalls->addItem(new Item("Huawei Secospace USG6380", "FIREWALLS", 209678.0, 1.8));
    firewalls->addItem(new Item("Zyxel USG310", "FIREWALLS", 1121622.0, 3.3));

    coolingSystems->addItem(new Item("Liquid Cooling System Unit LCU DX", "COOLING_SYSTEMS", 1621054.0, 24.0));
    coolingSystems->addItem(new Item("Samsung Prestige", "COOLING_SYSTEMS", 1844954.0, 21.0));
    coolingSystems->addItem(new Item("Top Therm Blue", "COOLING_SYSTEMS", 1991304.0, 20.0));
    coolingSystems->addItem(new Item("Panasonic E9PKEA", "COOLING_SYSTEMS", 2315786.0, 22.0));

    connections->addItem(new Item("Łącze symetryczne, światłowodowe FTTB (wysoka niezawodność)", "CONNECTIONS", 5315786.0, 0.5));
    connections->addItem(new Item("Łącze asymetryczne, szerokopasmowe ADSL (normalna niezawodność)", "CONNECTIONS", 209678.0, 0.5));
    connections->addItem(new Item("Łącze satelitarne (niska niezawodność)", "CONNECTIONS", 96670.0, 0.5));

    serverSystem = new SerialSystem("Serwerownia");
    serverSystem->addItems(new ParallelSystem("Dyski"));
    serverSystem->addItems(new ParallelSystem("Routery"));
    serverSystem->addItems(new ParallelSystem("Zasilacze"));
    serverSystem->addItems(new ParallelSystem("Agregaty"));
    serverSystem->addItems(new ParallelSystem("Switche"));
    serverSystem->addItems(new ParallelSystem("Firewalle"));
    serverSystem->addItems(new ParallelSystem("Systemy chłodzenia"));
    serverSystem->addItems(new ParallelSystem("Połączenia"));
}

VPSSerwer::~VPSSerwer() {
    delete ui;
}

void VPSSerwer::on_addHDD_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj dysk twardy");
    pch->addItemsGroup(hardDrives);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Dyski");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->disks->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addPowerSupply_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj zasilacz");
    pch->addItemsGroup(powerSupplies);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Zasilacze");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->powerSupplies->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addFirewall_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj zaporę ogniową");
    pch->addItemsGroup(firewalls);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Firewalle");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->firewalls->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addRouter_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj router");
    pch->addItemsGroup(routers);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Routery");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->routers->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addPowerUnit_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj agregat prądotwórczy");
    pch->addItemsGroup(powerUnits);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Agregaty");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->powerUnits->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addCoolingSystem_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj układ chłodzący");
    pch->addItemsGroup(coolingSystems);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Systemy chłodzenia");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->coolingSystems->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addSwitch_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj przełącznik");
    pch->addItemsGroup(switches);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Switche");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->switches->addItem(item->getName());
        }
    }
}

void VPSSerwer::on_addConnection_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj połączenie sieciowe");
    pch->addItemsGroup(connections);
    pch->setModal(true);
    pch->exec();
    ItemsGroup *groupToAdd = pch->getItemsChoosen();
    if(groupToAdd->getCount() > 0){
        ParallelSystem *ps = serverSystem->getParallelSystemByName("Połączenia");
        QList<Item*> itemsToAdd = groupToAdd->getItems();
        foreach(Item* item, itemsToAdd){
            ps->addItem(item);
            ui->connections->addItem(item->getName());
        }
    }
}
