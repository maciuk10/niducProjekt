#ifndef GENERATESURVEY_H
#define GENERATESURVEY_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class GenerateSurvey;
}

class GenerateSurvey : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateSurvey(QWidget *parent = nullptr);
    QMap<QString, QString> getConfiguration();
    ~GenerateSurvey();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

    void on_fixedCount_clicked();

    void on_randomCount_clicked();

private:
    Ui::GenerateSurvey *ui;
};

#endif // GENERATESURVEY_H
