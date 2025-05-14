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

struct RangeData {
    int minValue;
    int maxValue;
    int assignedValue;
    int accValue;
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

    int uploadFileWithSftpUPdate( QString localFile,
                                            QString remoteUser,
                                            QString remoteHost,
                                            QString remotePath,
                                            int port,             // 新增端口参数
                                            QWidget *parent);

private slots:
    void allInsertPaus();
    void allDeletePaus();
    void insertPaus();
    void deleteLine();

    void addRangeRow();
    void on_saveBtn_clicked();

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
