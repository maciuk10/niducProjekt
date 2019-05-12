#ifndef VPSSERWER_H
#define VPSSERWER_H

#include <QMainWindow>
#include <QTabBar>
#include <QMessageBox>
#include <QTime>
#include <chrono>
#include <thread>
#include "parameterschooser.h"
#include "itemsgroup.h"
#include "parallelsystem.h"
#include "serialsystem.h"
#include "qcustomplot.h"
#include "generatesurvey.h"
#include "gaussrandomgenerator.h"

using namespace std::this_thread;
using namespace std::chrono;

namespace Ui {
class VPSSerwer;
}

class VPSSerwer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VPSSerwer(QWidget *parent = nullptr);
    ~VPSSerwer();
    QString formatDoubleHours(double hours);
    int getDaysCount(double hours);
    void initializePlot();
    void displaySLALevels(double value);
    double getDoubleLabelValue(QLabel *label);
    double getDoubleLabelValue(QString str);
    void preparePlotsData(double downtime);
    double randomFloat(int _from, int _to, int n);
    int tenPow(unsigned int n);
    double hoursToDays(double hours);
    bool isInZero(double element);
    double getConstReliabilityProcent() const;
    void setConstReliabilityProcent(double value);
    double getReliabilityFromComboBox(QString value);
    double getMttrToDecrease() const;
    void setMttrToDecrease(double value);
    void resetSystem();
    void updateReliabilityLabels();
    void addElementToSystem(double desiredReliability, bool add);
    void removeCheckedItems();
    void decreaseMttr(double procent);
    void renewElement(double criticalReliability);
    QMap<int, int> prepareChartsData(int downtime, int momentsCount);
    QMap<int, double> prepareChartsData2(int downtime, int momentsCount);

private slots:
    void on_addHDD_clicked();
    void on_addPowerSupply_clicked();
    void on_addFirewall_clicked();
    void on_addRouter_clicked();
    void on_addPowerUnit_clicked();
    void on_addCoolingSystem_clicked();
    void on_addSwitch_clicked();
    void on_addConnection_clicked();
    void on_pushButton_clicked();
    void on_designMenu_clicked();
    void on_startDrawing_clicked();
    void realtimeDataSlot();
    void on_nextYear_clicked();
    void on_resetSystem_clicked();
    void on_constReliability_stateChanged(int arg1);
    void on_ownService_clicked();
    void on_outsideService_clicked();

    void on_startDrawing_2_clicked();

    void on_generateDataBtn_clicked();

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
    QTimer *datatimer;
    QList<int> breakMoments;
    QList<double> breakTimes;
    QCustomPlot *plot;
    bool nextPlot;
    double constReliabilityProcent;
    double mttrToDecrease;
    GaussRandomGenerator *gauss;
    GaussRandomGenerator *moments;
};

#endif // VPSSERWER_H
