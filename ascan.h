#ifndef ASCAN_H
#define ASCAN_H

#include <QWidget>

namespace Ui {
class ascan;
}

class ascan : public QWidget
{
    Q_OBJECT

public:
    explicit ascan(QWidget *parent = nullptr);
    ~ascan();

private:
    Ui::ascan *ui;
};

#endif // ASCAN_H
