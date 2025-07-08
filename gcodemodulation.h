#ifndef GCODEMODULATION_H
#define GCODEMODULATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QObject>
#include <cmath>

struct RangeData {
    int minValue;
    int maxValue;
    int assignedValue;
    int accValue;
};

struct Point {
    float x, y, z;
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
    QString workPiece;

    void loadGCodeToPlainText();
    void exportGCodeToFile(const QString& gCode);
    std::pair<int, int> getValueByRange(int input);
    double calculateRadius(double endX, double endY, double centerI, double centerJ);

    int uploadFileWithSftp();

    Point getPointAtDistance(float x0, float y0, float z0,
                             float x1, float y1, float z1,
                             float distance);

    bool deleteRemoteFile(const QString& workPiece);

    bool isHostOnline(const QString& host, quint16 port = 22, int timeoutMs = 3000);
private slots:
    void allInsertPaus();
    void allDeletePaus();
    void insertPaus();
    void deleteLine();

    void autoSave();

    void addRangeRow();
    void on_saveBtn_clicked();

    void on_trajectory_smooth_clicked();

    void TransmissionFile();


private:
    Ui::gCodeModulation *ui;
    QVBoxLayout *rangeLayout;

    struct RangeRow {
        QWidget* container;
        QSpinBox* minBox;
        QSpinBox* maxBox;
        QSpinBox* vBox;
        QSpinBox* accBox;
    };
    QList<RangeRow> rangeRows;

    QList<RangeData> savedRanges;
};

#endif // GCODEMODULATION_H
