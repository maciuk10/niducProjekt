#include "parameterschooser.h"
#include "ui_parameterschooser.h"

ParametersChooser::ParametersChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametersChooser)
{
    ui->setupUi(this);
}

ParametersChooser::~ParametersChooser()
{
    delete ui;
}
