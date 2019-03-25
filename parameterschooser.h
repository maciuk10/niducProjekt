#ifndef PARAMETERSCHOOSER_H
#define PARAMETERSCHOOSER_H

#include <QDialog>

namespace Ui {
class ParametersChooser;
}

class ParametersChooser : public QDialog
{
    Q_OBJECT

public:
    explicit ParametersChooser(QWidget *parent = nullptr);
    ~ParametersChooser();

private:
    Ui::ParametersChooser *ui;
};

#endif // PARAMETERSCHOOSER_H
