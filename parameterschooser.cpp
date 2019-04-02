#include "parameterschooser.h"
#include "ui_parameterschooser.h"

ParametersChooser::ParametersChooser(QWidget *parent, QString title) :
    QDialog(parent),
    title(title),
    ui(new Ui::ParametersChooser) {
    ui->setupUi(this);
    this->setWindowTitle(this->title);
}

ParametersChooser::~ParametersChooser() {
    delete ui;
}

void ParametersChooser::addItemsGroup(ItemsGroup *items) {
    currentItems = items;
    int itemsCount = currentItems->getCount();
    for(int i = 0; i < itemsCount; i++){
        ui->deviceName->addItem(currentItems->getItems().at(i)->getName());
    }
    ui->distributionType->addItem("Rozkład Wykładniczy");
    ui->distributionType->addItem("Rozkład Weibulla");
}

ItemsGroup *ParametersChooser::getItemsChoosen() {
    ItemsGroup *group;
    QString itemName = ui->deviceName->currentText();
    int itemCount = ui->itemsCount->text().toInt();
    double mtbf, mttr, mttf;
    mtbf = ui->mtbf->text().toDouble();
    mttr = ui->mttr->text().toDouble();
    mttf = ui->mttf->text().toDouble();
    group = new ItemsGroup();
    for(int i = 0; i < itemCount; i++){
        Item *item = new Item(itemName, this->itemsType, mtbf, mttr);
        if(ui->mtbf->isEnabled() == false){
            item->setDistribution(ui->distributionType->currentText());
        }
        item->setAvailability(0);
        group->addItem(item);
    }
    return group;
}

void ParametersChooser::on_deviceName_currentIndexChanged(const QString &arg1) {
    Item *item = currentItems->getItemByName(arg1);
    if(item){
        ui->mtbf->setVisible(true);
        ui->mttr->setVisible(true);
        ui->mttf->setVisible(true);
        ui->mtbf_label->setVisible(true);
        ui->mttf_label->setVisible(true);
        ui->mttr_label->setVisible(true);
        ui->constAvailability->setChecked(true);
        ui->distributionType->setDisabled(true);
        ui->mtbf->setDisabled(false);
        ui->mttf->setDisabled(false);
        ui->mttr->setDisabled(false);
        ui->mtbf->setText(QString::number(item->getMtbf(), 'g', 10));
        ui->mttf->setText(QString::number(item->getMttf(), 'g', 10));
        ui->mttr->setText(QString::number(item->getMttr(), 'g', 10));
    }
}

void ParametersChooser::on_timeBasedAvailability_clicked() {
    ui->distributionType->setEnabled(true);
    ui->mtbf->setDisabled(true);
    ui->mttf->setDisabled(true);
    ui->mttr->setDisabled(true);
}

void ParametersChooser::on_constAvailability_clicked() {
    ui->distributionType->setEnabled(false);
    ui->mtbf->setDisabled(false);
    ui->mttf->setDisabled(false);
    ui->mttr->setDisabled(false);
}

void ParametersChooser::on_buttonBox_accepted() {
    getItemsChoosen();
}

void ParametersChooser::setItemsType(QString itemsType) {
    this->itemsType = itemsType;
}
