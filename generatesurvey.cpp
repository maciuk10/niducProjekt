#include "generatesurvey.h"
#include "ui_generatesurvey.h"

GenerateSurvey::GenerateSurvey(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateSurvey)
{
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Generuj");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Zamknij");
}

QMap<QString, QString> GenerateSurvey::getConfiguration() {
    QMap<QString, QString> conf;
    if(ui->dataType->currentIndex()){
        conf.insert("type", "term");
    }else {
        conf.insert("type", "count");
    }
    conf.insert("times", ui->timesCount->text());
    if(ui->fixedCount_Value->isEnabled()){
        conf.insert("count", ui->fixedCount_Value->text());
    }else {
        conf.insert("count", "random");
    }
    return conf;
}

GenerateSurvey::~GenerateSurvey()
{
    delete ui;
}

void GenerateSurvey::on_buttonBox_rejected() {
    this->close();
}

void GenerateSurvey::on_buttonBox_accepted() {
    getConfiguration();
    this->close();
}

void GenerateSurvey::on_fixedCount_clicked() {
    ui->fixedCount_Value->setEnabled(true);
}

void GenerateSurvey::on_randomCount_clicked() {
    ui->fixedCount_Value->setEnabled(false);
}
