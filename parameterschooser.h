#ifndef PARAMETERSCHOOSER_H
#define PARAMETERSCHOOSER_H

#include <QDialog>
#include <QString>
#include <QMap>
#include "itemsgroup.h"

namespace Ui {
class ParametersChooser;
}

class ParametersChooser : public QDialog
{
    Q_OBJECT

public:
    explicit ParametersChooser(QWidget *parent = nullptr, QString title = "Dodaj element");
    ~ParametersChooser();
    void addItemsGroup(ItemsGroup* items);
    ItemsGroup *getItemsChoosen();

private slots:
    void on_deviceName_currentIndexChanged(const QString &arg1);
    void on_timeBasedAvailability_clicked();
    void on_constAvailability_clicked();
    void on_buttonBox_accepted();

private:
    QString title;
    Ui::ParametersChooser *ui;
    ItemsGroup *currentItems;
};

#endif // PARAMETERSCHOOSER_H
