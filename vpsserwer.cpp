#include "vpsserwer.h"
#include "ui_vpsserwer.h"


VPSSerwer::VPSSerwer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VPSSerwer) {
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    plot = new QCustomPlot();
    ui->plotBox->layout()->addWidget(plot);
    hardDrives = new ItemsGroup();
    routers = new ItemsGroup();
    switches = new ItemsGroup();
    powerSupplies = new ItemsGroup();
    powerUnits = new ItemsGroup();
    coolingSystems = new ItemsGroup();
    connections = new ItemsGroup();
    firewalls = new ItemsGroup();

    nextPlot = false;

    gauss = new GaussRandomGenerator(0.0, 350.0);
    moments = new GaussRandomGenerator(0.0, 1.0);

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

    setConstReliabilityProcent(0);
    setMttrToDecrease(0);

    srand(time(NULL));
    datatimer = new QTimer(this);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
    connect(datatimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
}

VPSSerwer::~VPSSerwer() {
    delete ui;
}

QString VPSSerwer::formatDoubleHours(double hrs) {
    QString response;
    int integerHours = (int)hrs;
    int days = integerHours / 24;
    int hours = integerHours % 24;
    int minutes = integerHours / 60;
    int seconds = integerHours % 60;
    double fraction = hrs - (int)hrs;
    fraction = fraction * 3600.0;
    int remainder = (int) fraction;
    minutes = minutes + (remainder / 60);
    seconds = seconds + (remainder % 60);
    if(seconds > 60){
       seconds = seconds % 60;
       minutes += seconds / 60;
    }
    if(minutes > 60){
       minutes = minutes % 60;
       hours += minutes / 60;
    }
    if(hours > 24){
       hours = hours % 24;
       days += hours / 24;
    }
    return response.sprintf("%.2d d %.2d h %.2d min %.2d sek",days,hours,minutes,seconds);
}

int VPSSerwer::getDaysCount(double hrs){
    QString response;
    int integerHours = (int)hrs;
    int days = integerHours / 24;
    int hours = integerHours % 24;
    int minutes = integerHours / 60;
    int seconds = integerHours % 60;
    double fraction = hrs - (int)hrs;
    fraction = fraction * 3600.0;
    int remainder = (int) fraction;
    minutes = minutes + (remainder / 60);
    seconds = seconds + (remainder % 60);
    if(seconds > 60){
       seconds = seconds % 60;
       minutes += seconds / 60;
    }
    if(minutes > 60){
       minutes = minutes % 60;
       hours += minutes / 60;
    }
    if(hours > 24){
       hours = hours % 24;
       days += hours / 24;
    }
    return days;
}

void VPSSerwer::on_addHDD_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj dysk twardy");
    pch->setItemsType("HARD_DRIVES");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_addPowerSupply_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj zasilacz");
    pch->setItemsType("POWER_SUPPLIES");
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
        ps->setReliability();
    }

}

void VPSSerwer::on_addFirewall_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj zaporę ogniową");
    pch->setItemsType("FIREWALLS");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_addRouter_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj router");
    pch->setItemsType("ROUTERS");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_addPowerUnit_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj agregat prądotwórczy");
    pch->setItemsType("POWER_UNTIS");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_addCoolingSystem_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj układ chłodzący");
    pch->setItemsType("COOLING_SYSTEMS");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_addSwitch_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj przełącznik");
    pch->setItemsType("SWITCHES");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_addConnection_clicked() {
    ParametersChooser *pch = new ParametersChooser(this, "Dodaj połączenie sieciowe");
    pch->setItemsType("CONNECTIONS");
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
        ps->setReliability();
    }
}

void VPSSerwer::on_pushButton_clicked() {
    QList<ParallelSystem*> components = serverSystem->getItems();
    serverSystem->setReliability();
    qDebug () << "Ustalono niezawodność całego systemu: "<< QString::number(serverSystem->getReliability(), 'f', 20);
    bool systemComplete = true;
    foreach(ParallelSystem* component, components){
        if(component->getItemsCount() == 0){
            systemComplete = false;
            break;
        }
    }
    if(systemComplete){
        ui->tabWidget->setCurrentIndex(1);
        ui->simulationMenu->setStyleSheet("background-color: rgba(255,255,255,0.1); border: none");
        ui->designMenu->setStyleSheet("background-color: transparent; border: none");
        if((int)serverSystem->getReliability() != 1){
            ui->params_totalReliability->setText(QString::number((serverSystem->getReliability()*100), 'f', 8)+"%");
        }else {
            ui->params_totalReliability->setText("99.99999999%");
        }
        ui->params_maxReliability->setText((serverSystem->getMaxElementReliability() != -1.0) ? QString::number((serverSystem->getMaxElementReliability()*100), 'f', 8)+"%" : "99.99999999%");
        ui->params_minReliability->setText((serverSystem->getMinElementReliability() != -1.0) ? QString::number((serverSystem->getMinElementReliability()*100), 'f', 8)+"%" : "99.99999999%");
        ui->params_yearOfUse->setText(QString::number(serverSystem->getYearOfWork()));
        ui->params_uptime->setText(formatDoubleHours(serverSystem->getUptime()));
        ui->params_downtime->setText(formatDoubleHours(serverSystem->getDowntime()));
        updateReliabilityLabels();
        preparePlotsData(hoursToDays(serverSystem->getDowntime()));
        displaySLALevels(getDoubleLabelValue(ui->params_totalReliability->text()));
    }else {
        QMessageBox::information(this, "Nie wybrano elementów", "Nie zostały wybrane wszystkie elementy niezbędne do działania systemu. Naciśnij przycisk + przy odpowiedniej grupie urządzeń dla których lista jest pusta");
    }
}

void VPSSerwer::on_designMenu_clicked() {
    ui->tabWidget->setCurrentIndex(0);
    ui->designMenu->setStyleSheet("background-color: rgba(255,255,255,0.1); border: none");
    ui->simulationMenu->setStyleSheet("background-color: transparent; border: none");
}

double VPSSerwer::hoursToDays(double hours){
    return hours * (0.04166666666667);
}

void VPSSerwer::initializePlot(){
    plot->addGraph();
    plot->graph()->setPen(QPen(QColor(40, 110, 255)));
    plot->xAxis->setRange(0,365);
    plot->axisRect()->setupFullAxesBox();
    plot->yAxis->setRange(-0.2, 1.2);
    plot->replot();
    delete datatimer;
    srand(time(NULL));
    datatimer = new QTimer(this);
    connect(datatimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
    datatimer->start(0);
}

void VPSSerwer::displaySLALevels(double value) {
    QList<QLabel*> slaLevels = ui->slaLavelsGB->findChildren<QLabel*>();
    foreach(QLabel* slaLevel, slaLevels){
            slaLevel->setStyleSheet("background-color: rgb(107,126,136); color: rgb(255,255,255); padding: 3px");
    }
    foreach(QLabel* slaLevel, slaLevels){
        if(getDoubleLabelValue(slaLevel) <= value){
            slaLevel->setStyleSheet("background-color: rgb(71,95,107); color: rgb(255,255,255); padding: 3px");
        }
    }
}

void VPSSerwer::preparePlotsData(double downtime){
    breakTimes.clear();
    breakMoments.clear();
    double countOfBreaks;
    double sum = downtime;
    countOfBreaks = rand() % ((int)downtime+10) + 1;
    for(int i = 0; i < countOfBreaks; i++){
        breakMoments.append(rand() % 350 + 1);
        if(i < countOfBreaks - 1){
            breakTimes.append(randomFloat(0, (int)sum / 6, 1));
            sum -= breakTimes.at(i);
        }
    }
    if(sum > 10.0){
        sum = 1.6;
    }
    breakTimes.append(sum);
}

QMap<int, double> VPSSerwer::prepareChartsData2(int downtime, int momentsCount){
    QMap<int, double> breaks;
    double sum = downtime;
    int countOfBreaks;
    if(momentsCount > 0){
        countOfBreaks = momentsCount;
    }else {
        countOfBreaks = rand() % ((int)downtime+10) + 5;
    }
    qDebug() << "Sum wynosi: "<< sum;
    for(int i = 0; i < countOfBreaks-1; i++){
        moments->setMax(sum);
        moments->setMin(0.0);
        double tmp = gauss->rand();
        breaks.insert((int)tmp, 0.0);
        double tmp_val = moments->rand();
        qDebug() << "Wylosowalem: "<<tmp_val;
        breaks[(int)tmp] = tmp_val;
        sum -= tmp_val;
    }
    double tmp2 = gauss->rand();
    breaks.insert((int)tmp2, 0.0);
    breaks[(int)tmp2] = sum;
    qDebug() << "Ostatni element ma: "<<breaks[(int)tmp2];

    return breaks;
}

QMap<int, int> VPSSerwer::prepareChartsData(int downtime, int momentsCount){
    QMap<int, int> breaks;
    int sum = downtime;
    int countOfBreaks;
    if(momentsCount > 0){
        countOfBreaks = momentsCount;
    }else {
        countOfBreaks = rand() % ((int)downtime+10) + 5;
    }
    for(int i = 0; i < countOfBreaks-1; i++){
        double tmp = gauss->rand();
        qDebug() << "Wygenerowałem tempa: " << tmp;
        breaks.insert((int)tmp, 0.0);
        int tmp_val = rand() % sum + 0;
        breaks[(int)tmp] = tmp_val;
        sum -= tmp_val;
    }
    double tmp2 = gauss->rand();
    breaks.insert((int)tmp2, 0);
    breaks[(int)tmp2] = sum;

    return breaks;
}

double VPSSerwer::randomFloat( int _from, int _to, int n ) {
    if(_from == _to){
       return 0;
    }
    return static_cast <double>(( rand() %(( _to - _from ) * tenPow( n ) ) ) +( _from * tenPow( n ) ) ) / tenPow( n );
}

int VPSSerwer::tenPow( unsigned int n ) {
    int base = 10;
    int res = 1.0;
    while( n > 0 ) {
        if( n & 1 )
             res *= base;
        base *= base;
        n >>= 1;
    }
    return res;
}


double VPSSerwer::getDoubleLabelValue(QLabel* label){
    QString str = label->text();
    QStringList parts = str.split("%");
    double result = parts.at(0).toDouble();
    return result;
}

double VPSSerwer::getDoubleLabelValue(QString str){
    QStringList parts = str.split("%");
    double result = parts.at(0).toDouble();
    return result;
}

void VPSSerwer::realtimeDataSlot() {
    static QTime time(QTime::currentTime());
    if(nextPlot){
        time.restart();
        nextPlot = !nextPlot;
    }
    double key = time.elapsed()/70.0;
    static double lastPointKey = 0;
    if (key-lastPointKey >= 0.1) {
        if(key >= 365.0){
            datatimer->stop();
            key = 0;
            lastPointKey = key;
            return;
        }
        if(isInZero(key)){
            plot->graph(0)->addData(key, 0);
        }else {
            plot->graph(0)->addData(key, 1);
        }
      lastPointKey = key;
    }
    plot->xAxis->setRange(key, 64, Qt::AlignRight);
    plot->replot();
}

bool VPSSerwer::isInZero(double element){
    for(int i = 0; i < breakMoments.count(); i++){
        if(element >= breakMoments.at(i) && element <= breakMoments.at(i)+breakTimes.at(i)){
            return true;
        }
    }
    return false;
}
void VPSSerwer::on_startDrawing_clicked() {
    preparePlotsData(hoursToDays(serverSystem->getDowntime()));
    initializePlot();
}

void VPSSerwer::on_nextYear_clicked() {
    serverSystem->setYearOfWork(serverSystem->getYearOfWork()+1);
    serverSystem->setReliability(serverSystem->getYearOfWork());
    double constReliability = getConstReliabilityProcent();
    if(getConstReliabilityProcent() != 0.0){
        if(serverSystem->getReliability() < constReliability){
            addElementToSystem(constReliability, false);
        }
    }
    if((int)serverSystem->getReliability() != 1){
        ui->params_totalReliability->setText(QString::number((serverSystem->getReliability()*100), 'f', 8)+"%");
    }else {
        ui->params_totalReliability->setText("99.99999999%");
    }
    ui->params_maxReliability->setText((serverSystem->getMaxElementReliability() != -1.0) ? QString::number((serverSystem->getMaxElementReliability()*100), 'f', 8)+"%" : "99.99999999%");
    ui->params_minReliability->setText((serverSystem->getMinElementReliability() != -1.0) ? QString::number((serverSystem->getMinElementReliability()*100), 'f', 8)+"%" : "99.99999999%");
    ui->params_yearOfUse->setText(QString::number(serverSystem->getYearOfWork()));
    ui->params_uptime->setText(formatDoubleHours(serverSystem->getUptime()));
    ui->params_downtime->setText(formatDoubleHours(serverSystem->getDowntime()));
    ui->plotBox->layout()->removeWidget(plot);
    plot = new QCustomPlot();
    ui->plotBox->layout()->addWidget(plot);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
    displaySLALevels(getDoubleLabelValue(ui->params_totalReliability->text()));
    nextPlot = true;
}

void VPSSerwer::removeCheckedItems(){
    QList<ParallelSystem*> systems = serverSystem->getItems();
    foreach(ParallelSystem* system, systems){
        QList<Item*> items = system->getItems();
        int count = items.count();
        for(int i = 0; i < count; i++){
            if(items[i]->getSwitched()){
                system->removeItem(items[i]);
            }
        }
    }
}

void VPSSerwer::decreaseMttr(double procent) {
    QList<ParallelSystem*> systems = serverSystem->getItems();
    foreach(ParallelSystem *system, systems){
        QList<Item*> items = system->getItems();
        foreach(Item *item, items){
            item->setMttr(item->getMttr() - ((procent/100.0) * item->getMttr()));
            item->calcMttf();
        }
    }
}

void VPSSerwer::on_resetSystem_clicked() {
    removeCheckedItems();
    ui->constReliability->setChecked(false);
    ui->constReliValue->setDisabled(true);
    ui->decreaseMTTR->setDisabled(true);
    ui->ownService->setChecked(false);
    ui->outsideService->setChecked(true);
    setConstReliabilityProcent(0.0);
    setMttrToDecrease(0.0);
    resetSystem();
}

void VPSSerwer::resetSystem() {
    ui->hardwareManager->clear();
    serverSystem->setYearOfWork(0);
    serverSystem->setReliability(serverSystem->getYearOfWork());
    double constReliability = getConstReliabilityProcent();
    if(getConstReliabilityProcent() != 0.0){
        if(serverSystem->getReliability() < constReliability){
            addElementToSystem(constReliability, true);
        }
    }
    if((int)serverSystem->getReliability() != 1){
        ui->params_totalReliability->setText(QString::number((serverSystem->getReliability()*100), 'f', 8)+"%");
    }else {
        ui->params_totalReliability->setText("99.99999999%");
    }
    ui->params_maxReliability->setText((serverSystem->getMaxElementReliability() != -1.0) ? QString::number((serverSystem->getMaxElementReliability()*100), 'f', 8)+"%" : "99.99999999%");
    ui->params_minReliability->setText((serverSystem->getMinElementReliability() != -1.0) ? QString::number((serverSystem->getMinElementReliability()*100), 'f', 8)+"%" : "99.99999999%");
    ui->params_yearOfUse->setText(QString::number(serverSystem->getYearOfWork()));
    ui->params_uptime->setText(formatDoubleHours(serverSystem->getUptime()));
    ui->params_downtime->setText(formatDoubleHours(serverSystem->getDowntime()));
    ui->plotBox->layout()->removeWidget(plot);
    updateReliabilityLabels();
    plot = new QCustomPlot();
    ui->plotBox->layout()->addWidget(plot);
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
    connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), plot->xAxis2, SLOT(setRange(QCPRange)));
    connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), plot->yAxis2, SLOT(setRange(QCPRange)));
    displaySLALevels(getDoubleLabelValue(ui->params_totalReliability->text()));
    nextPlot = true;
}

void VPSSerwer::updateReliabilityLabels() {
    QList<QLabel*> labels = ui->parametersBox->findChildren<QLabel*>();
    foreach(QLabel* label, labels){
        if(label->objectName().contains("params")){
            QString lbl_str = label->text();
            if(lbl_str == "100.00000000%"){
                label->setText("99.99999999%");
            }
        }
    }
}

void VPSSerwer::addElementToSystem(double desiredReliability, bool add) {
    desiredReliability = desiredReliability / 100.0;
    QList<ParallelSystem*> parallels = serverSystem->getItems();
    while(serverSystem->getReliability() < desiredReliability){
        double min = 100.0;
        ParallelSystem *minSys;
        foreach(ParallelSystem* parallel, parallels){
            if(parallel->getReliability() < min){
                min = parallel->getReliability();
                minSys = parallel;
            }
        }
        int index = rand() % (minSys->getItemsCount());
        Item* addedItem = minSys->getItem(index);
        Item* itemToAdd = new Item(addedItem->getName(), addedItem->getType(), addedItem->getMtbf(), addedItem->getMttr());
        itemToAdd->setDistribution("Rozkład Wykładniczy");
        itemToAdd->setSwitched(true);
        itemToAdd->setYear(0);
        itemToAdd->setAvailability(itemToAdd->getYear());
        minSys->addItem(itemToAdd);
        if(add){
            ui->hardwareManager->addItem("Dodano element systemu    :   "+itemToAdd->getName());
        }else {
            ui->hardwareManager->addItem("Wymieniono element systemu:   "+itemToAdd->getName());
        }
        serverSystem->setReliability(serverSystem->getYearOfWork());
    }
}

double VPSSerwer::getConstReliabilityProcent() const {
    return constReliabilityProcent;
}

void VPSSerwer::setConstReliabilityProcent(double value) {
    constReliabilityProcent = value;
}

void VPSSerwer::on_constReliability_stateChanged(int state) {
    if(state){
        ui->constReliValue->setEnabled(true);
    }else {
        ui->constReliValue->setEnabled(false);
    }
}


void VPSSerwer::on_ownService_clicked() {
    if(ui->ownService->isChecked()){
        ui->decreaseMTTR->setEnabled(true);
    }else {
        ui->decreaseMTTR->setEnabled(false);
    }
}

void VPSSerwer::on_outsideService_clicked() {
    ui->decreaseMTTR->setEnabled(false);
}

double VPSSerwer::getReliabilityFromComboBox(QString value){
    return value.split("%").at(0).toDouble();
}

void VPSSerwer::on_startDrawing_2_clicked() {
    if(ui->constReliValue->isEnabled()){
        setConstReliabilityProcent(getReliabilityFromComboBox(ui->constReliValue->currentText()));
    }else {
        setConstReliabilityProcent(0);
    }
    if(ui->ownService->isChecked()){
        setMttrToDecrease(getReliabilityFromComboBox(ui->decreaseMTTR->currentText()));
        decreaseMttr(getMttrToDecrease());
    }
    if(ui->outsideService->isChecked()){
        setMttrToDecrease(0);
    }
    QMessageBox::information(this, "Ustawiono pomyślnie", "Zmiany zostały wprowadzone pomyślnie");
    resetSystem();
}

double VPSSerwer::getMttrToDecrease() const {
    return mttrToDecrease;
}

void VPSSerwer::setMttrToDecrease(double value) {
    mttrToDecrease = value;
}

void VPSSerwer::on_generateDataBtn_clicked() {
    QList<ParallelSystem*> components = serverSystem->getItems();
    bool systemComplete = true;
    foreach(ParallelSystem* component, components){
        if(component->getItemsCount() == 0){
            systemComplete = false;
            break;
        }
    }
    if(!systemComplete){
        QMessageBox::information(this, "Nie wybrano elementów", "Nie zostały wybrane wszystkie elementy niezbędne do działania systemu. Naciśnij przycisk + przy odpowiedniej grupie urządzeń dla których lista jest pusta");
        return;
    }else {
        GenerateSurvey *gs = new GenerateSurvey(this);
        gs->setModal(true);
        gs->exec();
        QMap<QString, QString> conf = gs->getConfiguration();
        serverSystem->setReliability();
        qDebug () << "Ustalono niezawodność całego systemu: "<< QString::number(serverSystem->getReliability(), 'f', 20);
        int daysDowntime = getDaysCount(serverSystem->getDowntime());
        qDebug() << "Ustalono downtime: "<< daysDowntime;
        int times = conf["times"].toInt();
        QString keysFile = "";
        QString valuesFile = "";
        moments = new GaussRandomGenerator(0.0, (double)daysDowntime);
        QList<QList<int>> resultFileDays;
        QList<QList<double>> resultFileMoments;
        for(int i = 0; i < times; i++){
            QMap<int, double> fileRow;
            if(conf["count"] != "random"){
                fileRow = prepareChartsData2(daysDowntime, conf["count"].toInt());
            }else {
                fileRow = prepareChartsData2(daysDowntime, 0);
            }
            QList<int> days;
            QList<double> moments;
            for(int e : fileRow.keys()){
                days.append(e);
                moments.append(fileRow.value(e));
            }
            resultFileDays.append(days);
            resultFileMoments.append(moments);
        }
        if(conf["type"] == "count"){
            QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz dane do pliku"), "", tr("CSV - Rozdzielany przecinkami (*.csv)"));
            if (fileName.isEmpty())
                    return;
                else {
                    QFile file(fileName);
                    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
                        QMessageBox::information(this, tr("Nie można otworzyć pliku"),
                            file.errorString());
                        return;
                    }
                    QTextStream out(&file);
                    for(int i = 0; i < resultFileDays.size(); i++){
                        for(int j = 0; j < resultFileDays[i].size(); j++){
                            out << resultFileDays[i][j] << ";";
                        }
                        out << "\n";
                    }
                }
        }else {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Zapisz dane do pliku"), "", tr("CSV - Rozdzielany przecinkami (*.csv)"));
            if (fileName.isEmpty())
                    return;
                else {
                    QFile file(fileName);
                    if (!file.open(QFile::WriteOnly |QFile::Truncate)) {
                        QMessageBox::information(this, tr("Nie można otworzyć pliku"),
                            file.errorString());
                        return;
                    }
                    QTextStream out(&file);
                    for(int i = 0; i < resultFileMoments.size(); i++){
                        for(int j = 0; j < resultFileMoments[i].size(); j++){
                            out << QString::number(resultFileMoments[i][j], 'g', 10) << ";";
                        }
                        out << "\n";
                    }
                }
        }
    }
}
