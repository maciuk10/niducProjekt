#ifndef VPSSERWER_H
#define VPSSERWER_H

#include <QMainWindow>

namespace Ui {
class VPSSerwer;
}

class VPSSerwer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VPSSerwer(QWidget *parent = nullptr);
    ~VPSSerwer();

private:
    Ui::VPSSerwer *ui;
};

#endif // VPSSERWER_H
