#ifndef GCODEMODULATION_H
#define GCODEMODULATION_H

#include <QWidget>

namespace Ui {
class gCodeModulation;
}

class gCodeModulation : public QWidget
{
    Q_OBJECT

public:
    explicit gCodeModulation(QWidget *parent = nullptr);
    ~gCodeModulation();

private:
    Ui::gCodeModulation *ui;
};

#endif // GCODEMODULATION_H
