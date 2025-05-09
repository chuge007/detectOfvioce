#ifndef GCODEMODULATION_H
#define GCODEMODULATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>

struct RangeData {
    int minValue;
    int maxValue;
    int assignedValue;
};

namespace Ui {
class gCodeModulation;
}

class gCodeModulation : public QWidget
{
    Q_OBJECT

public:
    explicit gCodeModulation(QWidget *parent = nullptr);
    ~gCodeModulation();

    QString gcodePath;
    QString gcode;
    QString filePath;
    void loadGCodeToPlainText();
    void exportGCodeToFile(const QString& gCode);
    int  getValueByRange(int input);
    double calculateRadius(double endX, double endY, double centerI, double centerJ);

private slots:
    void allInsertPaus();
    void allDeletePaus();
    void insertPaus();
    void deleteLine();

    void addRangeRow();
    void on_saveBtn_clicked();

private:
    Ui::gCodeModulation *ui;
    QVBoxLayout *rangeLayout;

    struct RangeRow {
        QWidget* container;
        QSpinBox* minBox;
        QSpinBox* maxBox;
        QSpinBox* valueBox;
    };
    QList<RangeRow> rangeRows;

    QList<RangeData> savedRanges;
};

#endif // GCODEMODULATION_H
