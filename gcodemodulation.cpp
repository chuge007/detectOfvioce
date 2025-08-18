#include "gcodemodulation.h"
#include "ui_gcodemodulation.h"
#include "MotionControl.h"
#include "widgetDefin/setStyleSheet.h"
#include "./libssh2_1.11.0_x64/libssh2.h"
#include "./libssh2_1.11.0_x64/libssh2_publickey.h"
#include "./libssh2_1.11.0_x64/libssh2_sftp.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include <QString>
#include <libssh2.h>
#include <libssh2_sftp.h>

#include <stdio.h>
#include <winsock2.h>
#include <libssh2.h>
#include <iostream>

#include <QMessageBox>
#include <QTextBlock>  // Include the full definition of QTextBlock
#include <QDir>
#include <QRegularExpression>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QScrollBar>
#include <QLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QObject>
#include <QProcess>
#include <QProgressDialog>
#include <QFileInfo>
#include <QThread>
#include <QDebug>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "libssh2.lib")

gCodeModulation::gCodeModulation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gCodeModulation)
{
    ui->setupUi(this);


    // 1) 新建一个 QWidget 作为 scrollArea 的内容区
    QWidget *dynamicContainer = new QWidget;
    // 2) 给它一个垂直布局
    QVBoxLayout *vlay = new QVBoxLayout(dynamicContainer);
    vlay->setContentsMargins(4,4,4,4);
    vlay->setSpacing(6);

    // 3) 把它挂载到 scrollArea
    ui->rangeContainer->setWidget(dynamicContainer);
    ui->rangeContainer->setWidgetResizable(true);
    ui->rangeContainer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->rangeContainer->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // 4) 保存布局指针供 addRangeRow 使用
    rangeLayout = vlay;
    // 连接“添加范围”按钮


    connect(ui->addRangeBtn, &QPushButton::clicked, this, &gCodeModulation::addRangeRow);
    connect(ui->saveVBtn, &QPushButton::clicked, this, &gCodeModulation::on_saveBtn_clicked);

    connect(ui->pbPaus, &QPushButton::clicked, this, &gCodeModulation::insertPaus);
    connect(ui->pbdeleteCodeLine, &QPushButton::clicked, this, &gCodeModulation::deleteLine);
    connect(ui->pbALLPaus, &QPushButton::clicked, this, &gCodeModulation::allInsertPaus);
    connect(ui->pbDeleteALLPaus, &QPushButton::clicked, this, &gCodeModulation::allDeletePaus);
    connect(ui->TransmissionBtn, &QPushButton::clicked,this, &gCodeModulation::TransmissionFile);
    connect(ui->trajectory_smooth_but, &QPushButton::clicked,this, &gCodeModulation::on_trajectory_smooth_clicked);

    connect(ui->pbAganStart, &QPushButton::clicked, MotionControl::scanDetectCtrl, &ScanControlAbstract::on_aganStartScanBtn_clicked);
    connect(ui->pTEgcode, &QPlainTextEdit::textChanged, this, &gCodeModulation::autoSave);
    gcodePath = QCoreApplication::applicationDirPath() + "/PlcLogic/";

    this->setStyleSheet(styleMcSheet);  // 在构造函数里给当前窗口用
    //ui->pTEgcode->setDocument(false);

    ui->pTEgcode->setMinimumHeight(1000);
    ui->pTEgcode->setMinimumWidth(600);
    ui->rangeContainer->setMinimumHeight(300);
    ui->rangeContainer->setMinimumWidth(700);

    ui->pTEgcode->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->pTEgcode->setReadOnly(false);  // 确保是可编辑的
    ui->pTEgcode->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->pTEgcode->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->pTEgcode->setWordWrapMode(QTextOption::NoWrap);
    qDebug() << "hbar max =" << ui->pTEgcode->horizontalScrollBar()->maximum(); // > 0 表示可滚
    qDebug() << "doc width =" << ui->pTEgcode->document()->idealWidth();
    qDebug() << "view width =" << ui->pTEgcode->viewport()->width();

}



gCodeModulation::~gCodeModulation()
{
    delete ui;
}

void gCodeModulation::loadGCodeToPlainText()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, QString::fromLocal8Bit("提示"),
                                  QString::fromLocal8Bit("是否重新加载数据？"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        // 执行重新加载操作
        exportGCodeToFile(gcode);
    }


    QFile file(filePath); // gcodePath 是 G 代码文件的路径

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();

    ui->pTEgcode->clear();
    ui->pTEgcode->setPlainText(content);

    file.close();
}

void gCodeModulation::allInsertPaus()
{
    // 1. 原始文本按行拆分
    // 默认就会保留空行
    QStringList lines = ui->pTEgcode->toPlainText().split('\n');


    // 2. 去除旧行号并重建
    QStringList out;
    int lineNum = 0;
    for (int i = 0; i < lines.size(); ++i) {
        // 去掉原行首的 Nxxx 和空白
        QString content = lines[i];
        content.remove(QRegularExpression(R"(^N\d+\s*)"));

        // 拼接新行号 + 原内容
        out << QString("N%1 %2").arg(lineNum).arg(content);
        lineNum += 10;

        // 对于非最后一行，再插入一条暂停指令
        if (i + 1 < lines.size()) {
            out << QString("N%1 M10 K10 L10").arg(lineNum);
            lineNum += 10;
        }
    }

    // 3. 将重建后的文本一次性写回编辑器
    ui->pTEgcode->setPlainText(out.join('\n'));

    // 4. 保存到文件

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("保存失败"),
                             QString::fromLocal8Bit("无法保存到 %1:\n%2")
                             .arg(filePath, file.errorString()));
        return;
    }
    QTextStream outFile(&file);
    outFile << ui->pTEgcode->toPlainText();
    file.close();

}


void gCodeModulation::autoSave(){

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("保存失败"),
                             QString::fromLocal8Bit("无法保存到 %1:\n%2")
                             .arg(filePath, file.errorString()));
        return;
    }
    QTextStream outFile(&file);
    outFile << ui->pTEgcode->toPlainText();
    file.close();


}

void gCodeModulation::allDeletePaus(){

    // 1. 按行拆分（保留空行）
    QStringList lines = ui->pTEgcode->toPlainText().split('\n');

    // 2. 过滤掉“暂停行”
    //    我们认为所有包含“ M10 K10 L10” 的行都是暂停行
    QStringList filtered;
    for (const QString &line : lines) {
        if (!line.contains(QRegularExpression(R"(\bM10\s+K10\s+L10\b)"))) {
            filtered << line;
        }
    }

    // 3. 重新去掉旧行号并按步长 10 重新编号
    QStringList out;
    int lineNum = 0;
    for (int i = 0; i < filtered.size(); ++i) {
        QString content = filtered[i];
        // 去掉原行的 Nxxx 前缀
        content.remove(QRegularExpression(R"(^N\d+\s*)"));
        // 加上新行号
        out << QString("N%1 %2").arg(lineNum).arg(content);
        lineNum += 10;
    }

    // 4. 一次性写回编辑器
    ui->pTEgcode->setPlainText(out.join('\n'));


    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("保存失败"),
                             QString::fromLocal8Bit("无法保存到 %1:\n%2")
                             .arg(filePath, file.errorString()));
        return;
    }
    QTextStream ts(&file);
    ts << ui->pTEgcode->toPlainText();
    file.close();




}

void gCodeModulation::insertPaus()
{
    QTextDocument *doc = ui->pTEgcode->document();
    int insertLine = ui->sbPausLine->value(); // 获取要插入的位置（行号）

    QTextBlock block = doc->findBlockByNumber(insertLine);
    if (!block.isValid()) {
        qWarning() << "Invalid line number:" << insertLine;
        return;
    }

    // 创建文本游标并定位到指定行的末尾
    QTextCursor cursor(block);
    cursor.movePosition(QTextCursor::EndOfBlock);
    cursor.insertBlock();

    // 插入暂停指令
    QString pauseText = "N%1  M10  K10  L10 ";
    cursor.insertText(pauseText.arg((insertLine+1)*10));

    // 更新后续行的行号
    int totalBlocks = doc->blockCount();
    for (int i = insertLine + 2; i < totalBlocks; i++) {
        QTextBlock currentBlock = doc->findBlockByNumber(i);
        if (!currentBlock.isValid())
            continue;

        QString lineText = currentBlock.text();
        QRegularExpression re(R"(^N(\d+)\s+)");
        QRegularExpressionMatch match = re.match(lineText);

        qDebug()<<i<<"  "<<lineText;

        if (match.hasMatch()) {
            int newLineNumber = (i) * 10;
            QString newLine = lineText;
            newLine.replace(re, QString("N%1 ").arg(newLineNumber));
            QTextCursor lineCursor(currentBlock);
            lineCursor.select(QTextCursor::BlockUnderCursor);
            lineCursor.removeSelectedText();
            lineCursor.insertText("\n"+newLine);
        }
    }


    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->pTEgcode->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, QString::fromLocal8Bit("保存失败"),
                             QString::fromLocal8Bit("无法保存到 %1:\n%2").arg(filePath, file.errorString()));
    }
}



void gCodeModulation::deleteLine()
{
    QTextDocument *doc = ui->pTEgcode->document();
    int deleteLine = ui->sbPausLine->value(); // 获取要删除的行号

    QTextBlock block = doc->findBlockByNumber(deleteLine);
    if (!block.isValid()) {
        qWarning() << "Invalid line number:" << deleteLine;
        return;
    }

    // 删除指定行
    QTextCursor cursor(block);
    cursor.select(QTextCursor::BlockUnderCursor);
    cursor.removeSelectedText();
    //cursor.deleteChar(); // 删除换行符
    cursor.insertText("\n");
    // 更新后续行的行号
    int totalBlocks = doc->blockCount();
    for (int i = deleteLine; i < totalBlocks; ++i) {
        QTextBlock currentBlock = doc->findBlockByNumber(i);
        if (!currentBlock.isValid())
            continue;

        QString lineText = currentBlock.text();
        QRegularExpression re(R"(^N(\d+)\s+)");
        QRegularExpressionMatch match = re.match(lineText);
        if (match.hasMatch()) {
            int newLineNumber = (i-1) * 10;
            QString newLine = lineText;
            newLine.replace(re, QString("N%1 ").arg(newLineNumber));
            QTextCursor lineCursor(currentBlock);
            lineCursor.select(QTextCursor::BlockUnderCursor);
            lineCursor.removeSelectedText();
            lineCursor.insertText(newLine+"\n");
        }
    }


    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->pTEgcode->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, QString::fromLocal8Bit("保存失败"),
                             QString::fromLocal8Bit("无法保存到 %1:\n%2").arg(filePath, file.errorString()));
    }
}



void gCodeModulation::exportGCodeToFile(const QString& gCode)
{


    QDir dir(gcodePath);
    if (!dir.exists()) {
        if (!dir.mkpath(gcodePath)) {
            qDebug() << "Failed to create directory:" << gcodePath;
            return;
        }
    }


    // 打开文件并写入内容
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << gCode;
        file.close();
    } else {
        qDebug() << "Can not open file:" << filePath;
    }


}



void gCodeModulation::addRangeRow()
{
    QWidget *rowWidget = new QWidget;
    QHBoxLayout *rowLayout = new QHBoxLayout(rowWidget);

    QSpinBox *minBox = new QSpinBox;
    QSpinBox *maxBox = new QSpinBox;
    QSpinBox *vBox = new QSpinBox;
    QSpinBox *accBox = new QSpinBox;
    QPushButton *deleteBtn = new QPushButton(QString::fromLocal8Bit("删除"));

    rowWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rowWidget->setMinimumHeight(30);
    rowLayout->setContentsMargins(4, 2, 4, 2);
    rowLayout->setSpacing(8);

    minBox->setRange(0, 1000);
    maxBox->setRange(0, 1000);
    vBox->setRange(0, 1000);
    accBox->setRange(0, 1000);



    rowLayout->addWidget(new QLabel(QString::fromLocal8Bit("范围:")));
    rowLayout->addWidget(minBox);
    rowLayout->addWidget(new QLabel("~"));
    rowLayout->addWidget(maxBox);
    rowLayout->addWidget(new QLabel(QString::fromLocal8Bit("v:")));
    rowLayout->addWidget(vBox);
    rowLayout->addWidget(new QLabel(QString::fromLocal8Bit("acc:")));
    rowLayout->addWidget(accBox);
    rowLayout->addWidget(deleteBtn);

    rangeLayout->addWidget(rowWidget);

    // 删除逻辑
    connect(deleteBtn, &QPushButton::clicked, this, [=]() {
        rangeLayout->removeWidget(rowWidget);
        rowWidget->deleteLater();
        // 可选：从列表中移除
        for (int i = 0; i < rangeRows.size(); ++i) {
            if (rangeRows[i].container == rowWidget) {
                rangeRows.removeAt(i);
                break;
            }
        }
    });

    // 存储组件引用
    RangeRow row;
    row.container = rowWidget;
    row.minBox = minBox;
    row.maxBox = maxBox;
    row.vBox = vBox;
    row.accBox = accBox;
    rangeRows.append(row);
}






void gCodeModulation::on_saveBtn_clicked()
{
    savedRanges.clear();

    for (const auto& row : rangeRows) {
        int minVal = row.minBox->value();
        int maxVal = row.maxBox->value();
        int val    = row.vBox->value();
        int acc    = row.accBox->value();

        // 可选：校验
        if (minVal > maxVal) std::swap(minVal, maxVal);

        savedRanges.append({minVal, maxVal, val,acc});
    }



    QStringList lines = ui->pTEgcode->toPlainText().split('\n');


    QStringList out;
    QRegularExpression commentLineRe("^\\s*\\(.*\\)\\s*$");  // 整行注释
    QRegularExpression cmdRe("\\b(G0[123])\\b");  // 匹配 G01、G02、G03

    for (const QString& line : lines) {
        QString trimmedLine = line.trimmed();
        QRegularExpressionMatch cmdMatch = cmdRe.match(trimmedLine);

        if (commentLineRe.match(line).hasMatch()){
            out.append(line);
            continue;}


        if (cmdMatch.hasMatch()) {
            QString cmd = cmdMatch.captured(1);  // 拿到 G01/G02/G03

            if (cmd == "G01") {
                // 直线运动，直接加固定速度/加速度
                QString newLine = trimmedLine +
                        QString(" F%1 E%2 E-%3")
                        .arg(ui->dsbLineV->value())
                        .arg(ui->dsbAccV->value())
                        .arg(ui->dsbAccV->value());
                out.append(newLine);
                qDebug() << "line (G01):" << newLine;

            } else if(cmd == "G02"||cmd == "G03"){
                // G02 或 G03 圆弧运动
                // 提取 X/Y/I/J
                QRegularExpression re("([XYIJ])([-\\d.]+)");
                QRegularExpressionMatchIterator it = re.globalMatch(trimmedLine);

                double x = 0, y = 0, i_val = 0, j_val = 0;
                while (it.hasNext()) {
                    auto m = it.next();
                    QString axis = m.captured(1);
                    double v = m.captured(2).toDouble();
                    if (axis == "X") x = v;
                    else if (axis == "Y") y = v;
                    else if (axis == "I") i_val = v;
                    else if (axis == "J") j_val = v;
                }

                double radius = calculateRadius(x, y, i_val, j_val);
                std::pair<int, int> result   = getValueByRange(static_cast<int>(radius));

                QString newLine = trimmedLine +
                        QString(" F%1 E%2 E-%3")
                        .arg(result.first)
                        .arg(result.second)
                        .arg(result.second);
                out.append(newLine);
                qDebug() << "arc (G02/G03):" << newLine;
            }

        } else {
            // 不含 G01/G02/G03 的行，原样保留
            out.append(trimmedLine);
        }
    }



    // 写回编辑器
    ui->pTEgcode->setPlainText(out.join('\n'));

    // 保存到文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("保存失败"),
                             tr("无法保存到 %1:\n%2").arg(filePath, file.errorString()));
        return;
    }
    QTextStream outFile(&file);
    outFile << ui->pTEgcode->toPlainText();
    file.close();


    qDebug() << "保存完成，总数:" << savedRanges.size();
}




QString generateG01Command(const Point& targetPoint, const QString& originalLine) {
    // 使用正则表达式提取出括号中的原始坐标
    QRegularExpression re(R"(\(N(\d+)\s+G01\s+XF\s*([\d\.-]+)\s+YF\s*([\d\.-]+)\s+ZF\s*([\d\.-]+)\s+XS\s*([\d\.-]+)\s+YS\s*([\d\.-]+)\s+ZS\s*([\d\.-]+)\s+A\s*([\d\.-]+)\))");
    QRegularExpressionMatch match = re.match(originalLine);

    if (match.hasMatch()) {
        // 提取原始 G-code 参数
        int lineNumber = match.captured(1).toInt();  // N%1
        float xf = match.captured(2).toFloat();  // XF%2
        float yf = match.captured(3).toFloat();  // YF%3
        float zf = match.captured(4).toFloat();  // ZF%4
        float xs = match.captured(5).toFloat();  // XS%5
        float ys = match.captured(6).toFloat();  // YS%6
        float zs = match.captured(7).toFloat();  // ZS%7
        float a = match.captured(8).toFloat();   // A%8

        // 构造新的 G01 指令，替换坐标
        QString newGCode = QString("N%1 G01 X%2 Y%3 Z%4  A%5")
                .arg(lineNumber)                      // N%1
                .arg(targetPoint.x, 0, 'f', 3)         // 新的 XF
                .arg(targetPoint.y, 0, 'f', 3)         // 新的 YF
                .arg(targetPoint.z, 0, 'f', 3)         // 新的 ZF
                .arg(a, 0, 'f', 3);                    // 保持原始 A%8

        return newGCode;
    }

    // 如果没有匹配，返回原始行
    return originalLine;
}


void gCodeModulation::on_trajectory_smooth_clicked(){



    QStringList lines = ui->pTEgcode->toPlainText().split('\n');


    for ( QString &line : lines) {
        // 正则表达式来匹配和提取相关数据
        QRegularExpression re(R"(\(N(\d+)\s+G01\s+XF\s*([\d\.-]+)\s+YF\s*([\d\.-]+)\s+ZF\s*([\d\.-]+)\s+XS\s*([\d\.-]+)\s+YS\s*([\d\.-]+)\s+ZS\s*([\d\.-]+)\s+A\s*([\d\.-]+)\))");


        QRegularExpressionMatch match = re.match(line);
        if (match.hasMatch()) {
            // 提取各个参数

            float x0 = match.captured(2).toFloat(); // XF
            float y0 = match.captured(3).toFloat(); // YF
            float z0 = match.captured(4).toFloat(); // ZF
            float x1 = match.captured(5).toFloat(); // XS
            float y1 = match.captured(6).toFloat(); // YS
            float z1 = match.captured(7).toFloat(); // ZS
            float a = match.captured(8).toFloat();  // A angle

            qDebug()<<"line"<<line;

            qDebug() << "Start Point: (" << x0 << ", " << y0 << ", " << z0 << ")";
            qDebug() << "End Point: (" << x1 << ", " << y1 << ", " << z1 << ")";
            qDebug() << "A Angle: " << a;


            float distance3D = std::sqrt(std::pow(x1 - x0, 2) +
                                         std::pow(y1 - y0, 2) +
                                         std::pow(z1 - z0, 2));
            // 获取距离参数，乘以 1.5
            float distance = ui->trajectory_smooth_dsb->value();
            qDebug()<<"distance3D :"<<distance3D;
            qDebug()<<"distance :"<<distance;
            if(distance3D<distance){continue;}
            qDebug()<<"line :"<<line;
            // 计算目标点，假设从 (x0, y0, z0) 到 (x1, y1, z1) 的路径
            Point targetPoint = getPointAtDistance(x0, y0, z0, x1, y1, z1, distance);

            line = generateG01Command(targetPoint, line);

            qDebug()<<"line :"<<line;
            // 输出计算后的目标点
            qDebug() << "targetPoint: (" << targetPoint.x << ", " << targetPoint.y << ", " << targetPoint.z << ")";
        } else {
            qDebug() << "not match G-code : " << line;
        }
    }





//    // 添加圆滑处理启用和关闭指令
//    lines.insert(0, QString("N000 G51 D%1").arg(ui->trajectory_smooth_dsb->value()));              // 第一行
//    int insertPos = lines.size() >= 1 ? lines.size() - 1 : lines.size();
//    lines.insert(insertPos, QString("N%1 G50").arg((lines.size()-1)*10));         // 倒数第二行


    // 写回编辑器
    ui->pTEgcode->setPlainText(lines.join('\n'));

    // 保存到文件
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("保存失败"),
                             tr("无法保存到 %1:\n%2").arg(filePath, file.errorString()));
        return;
    }
    QTextStream outFile(&file);
    outFile << ui->pTEgcode->toPlainText();
    file.close();


    qDebug() << "保存完成，总数:" << savedRanges.size();



}




//void gCodeModulation::on_trajectory_smooth_clicked(){



//    QStringList lines = ui->pTEgcode->toPlainText().split('\n');


//    for ( QString &line : lines) {
//        // 正则表达式来匹配和提取相关数据
//        QRegularExpression re(R"(\(N%(\d+) XF(\d+(\.\d+)?) YF(\d+(\.\d+)?) ZF(\d+(\.\d+)?) XS(\d+(\.\d+)?) YS(\d+(\.\d+)?) ZS(\d+(\.\d+)?) A(\d+(\.\d+)?)\))");

//        QRegularExpressionMatch match = re.match(line);
//        if (match.hasMatch()) {
//            // 提取各个参数
//            float x0 = match.captured(2).toFloat();
//            float y0 = match.captured(4).toFloat();
//            float z0 = match.captured(6).toFloat();
//            float x1 = match.captured(8).toFloat();
//            float y1 = match.captured(10).toFloat();
//            float z1 = match.captured(12).toFloat();
//            float x2 = match.captured(14).toFloat();
//            float y2 = match.captured(16).toFloat();
//            float z2 = match.captured(18).toFloat();
//            float a = match.captured(20).toFloat();

//            // 获取距离参数，乘以 1.5
//            float distance = ui->trajectory_smooth_dsb->value() * 1.5;

//            // 计算目标点，假设从 (x0, y0, z0) 到 (x1, y1, z1) 的路径
//            Point targetPoint = getPointAtDistance(x0, y0, z0, x1, y1, z1, distance);

//            line = generateG01Command(targetPoint, line);
//            // 输出计算后的目标点
//            qDebug() << "targetPoint: (" << targetPoint.x << ", " << targetPoint.y << ", " << targetPoint.z << ")";
//        } else {
//            qDebug() << "not match G-code : " << line;
//        }
//    }





//    // 添加圆滑处理启用和关闭指令
//    lines.insert(0, QString("N000 G51 D%1").arg(ui->trajectory_smooth_dsb->value()));              // 第一行
//    int insertPos = lines.size() >= 1 ? lines.size() - 1 : lines.size();
//    lines.insert(insertPos, QString("N%1 G50").arg((lines.size()-1)*10));         // 倒数第二行


//    // 写回编辑器
//    ui->pTEgcode->setPlainText(lines.join('\n'));

//    // 保存到文件
//    QFile file(filePath);
//    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QMessageBox::warning(this, tr("保存失败"),
//                             tr("无法保存到 %1:\n%2").arg(filePath, file.errorString()));
//        return;
//    }
//    QTextStream outFile(&file);
//    outFile << ui->pTEgcode->toPlainText();
//    file.close();


//    qDebug() << "保存完成，总数:" << savedRanges.size();



//}

std::pair<int, int> gCodeModulation::getValueByRange(int input) {
    for (const auto& r : savedRanges) {
        if (input >= r.minValue && input <= r.maxValue) {
            return std::make_pair(r.assignedValue, r.accValue);
        }
    }

    // 如果没有匹配的范围，返回默认值
    return std::make_pair(ui->dsbLineV->value(), ui->dsbAccV->value());
}



double gCodeModulation::calculateRadius(double endX, double endY, double centerI, double centerJ)
{
    double centerX = endX + centerI;
    double centerY = endY + centerJ;
    return std::hypot(endX - centerX, endY - centerY);
}







void gCodeModulation::TransmissionFile(){

    QStringList lines = ui->pTEgcode->toPlainText().split('\n');
    bool hasE = false;

    for (const QString &line : lines) {
        if (line.contains('E')) {
            hasE = true;
            break;  // 找到就不再检查其他行
        }
    }

    if (!hasE) {
        QMessageBox::warning(this,
            QString::fromLocal8Bit("提示"),
            QString::fromLocal8Bit("没有速度参数，请先保存速度！"));
        return;  // 或者 return 某个值，或执行你的后续逻辑
    }

    uploadFileWithSftp();

}


bool gCodeModulation::isHostOnline(const QString& host, quint16 port, int timeoutMs) {
    QTcpSocket socket;
    socket.connectToHost(host, port);

    if (!socket.waitForConnected(timeoutMs)) {
        QMessageBox::warning(nullptr, QString::fromLocal8Bit("提示"),
                             QString::fromLocal8Bit("无法联系到客户端，请检查线路"));
        return false;
    }

    return true;
}

int gCodeModulation::uploadFileWithSftp()
{

    if (!isHostOnline("192.168.1.88")) {
        qDebug() << "目标主机不可达";
        return false;
    }

    // Upload progress dialog
    QProgressDialog progress("Uploading...", "Cancel", 0, 100, nullptr);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    progress.setValue(0);

    QString remotePath = "./PlcLogic/_cnc/" + workPiece + ".cnc";
    const char *hostname = "192.168.1.88";
    const char *username = "update";
    const char *password = "123456";
    std::string remotePathStr = remotePath.toStdString();
    const char *remoteFilePath = remotePathStr.c_str();

    std::string localPathStr = filePath.toStdString();
    const char *localFilePath = localPathStr.c_str();

    int port = 22;

    // Initialize libssh2
    if (libssh2_init(0) != 0) {
        QMessageBox::critical(nullptr, "Error", "Failed to initialize libssh2");
        return -1;
    }

    // Initialize socket
    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 0), &wsadata) != 0) {
        QMessageBox::critical(nullptr, "Error", "WSAStartup initialization failed");
        libssh2_exit();
        return -1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(hostname);

    if (::connect(sock, (struct sockaddr*)(&sin), sizeof(sin)) != 0) {
        QMessageBox::critical(nullptr, "Error", "Failed to connect to remote host");
        closesocket(sock);
        WSACleanup();
        libssh2_exit();
        return -1;
    }

    // Create SSH session
    LIBSSH2_SESSION *session = libssh2_session_init();
    if (!session || libssh2_session_handshake(session, sock) != 0) {
        QMessageBox::critical(nullptr, "Error", "SSH handshake failed");
        closesocket(sock);
        WSACleanup();
        libssh2_exit();
        return -1;
    }

    // Authenticate
    if (libssh2_userauth_password(session, username, password) != 0) {
        QMessageBox::critical(nullptr, "Error", "SSH authentication failed");
        libssh2_session_disconnect(session, "bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        libssh2_exit();
        return -1;
    }

    // Initialize SFTP
    LIBSSH2_SFTP *sftp_session = libssh2_sftp_init(session);
    if (!sftp_session) {
        QMessageBox::critical(nullptr, "Error", "SFTP initialization failed");
        libssh2_session_disconnect(session, "bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        libssh2_exit();
        return -1;
    }

    // Open remote file (retry up to 3 times)
    LIBSSH2_SFTP_HANDLE *file_handle = nullptr;
    const int MAX_RETRY = 3;
    for (int i = 0; i < MAX_RETRY; ++i) {
        file_handle = libssh2_sftp_open(sftp_session, remoteFilePath,
                                        LIBSSH2_FXF_WRITE | LIBSSH2_FXF_CREAT | LIBSSH2_FXF_TRUNC,
                                        LIBSSH2_SFTP_S_IRUSR | LIBSSH2_SFTP_S_IWUSR |
                                        LIBSSH2_SFTP_S_IRGRP | LIBSSH2_SFTP_S_IROTH);
        if (file_handle)
            break;

        QThread::msleep(1000);
    }

    if (!file_handle) {
        QMessageBox::critical(nullptr, "Error", "Cannot open remote file for writing");
        libssh2_sftp_shutdown(sftp_session);
        libssh2_session_disconnect(session, "bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        libssh2_exit();
        return -1;
    }

    // Open local file
    FILE *local = fopen(localFilePath, "rb");
    if (!local) {
        QMessageBox::critical(nullptr, "Error", "Cannot open local file");
        libssh2_sftp_close(file_handle);
        libssh2_sftp_shutdown(sftp_session);
        libssh2_session_disconnect(session, "bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        libssh2_exit();
        return -1;
    }

    fseek(local, 0, SEEK_END);
    long totalSize = ftell(local);
    fseek(local, 0, SEEK_SET);

    long transferred = 0;
    char buffer[32768];
    size_t n;

    // Upload file
    while ((n = fread(buffer, 1, sizeof(buffer), local)) > 0) {
        char *p = buffer;
        while (n > 0) {
            ssize_t written = libssh2_sftp_write(file_handle, p, n);
            if (written < 0) {
                QMessageBox::critical(nullptr, "Error", "Failed to write to remote file");
                fclose(local);
                libssh2_sftp_close(file_handle);
                libssh2_sftp_shutdown(sftp_session);
                libssh2_session_disconnect(session, "bye");
                libssh2_session_free(session);
                closesocket(sock);
                WSACleanup();
                libssh2_exit();
                return -1;
            }

            p += written;
            n -= written;
            transferred += written;

            int percent = static_cast<int>((transferred * 100) / totalSize);
            progress.setValue(percent);
            qApp->processEvents();

            if (progress.wasCanceled()) {
                QMessageBox::warning(nullptr, "Cancelled", "Upload cancelled");
                fclose(local);
                libssh2_sftp_close(file_handle);
                libssh2_sftp_shutdown(sftp_session);
                libssh2_session_disconnect(session, "bye");
                libssh2_session_free(session);
                closesocket(sock);
                WSACleanup();
                libssh2_exit();
                return -1;
            }
        }
    }

    // Cleanup resources
    fclose(local);
    libssh2_sftp_close(file_handle);
    libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "bye");
    libssh2_session_free(session);
    closesocket(sock);
    WSACleanup();
    libssh2_exit();
    progress.close();

    QMessageBox::information(nullptr, QString::fromLocal8Bit("信息"),
                             QString::fromLocal8Bit("g代码传输完成"));
    return 0;
}





Point gCodeModulation::getPointAtDistance(float x0, float y0, float z0,
                                          float x1, float y1, float z1,
                                          float distance) {
    // Calculate the straight-line distance in 3D space
    float distance3D = std::sqrt(std::pow(x1 - x0, 2) +
                                 std::pow(y1 - y0, 2) +
                                 std::pow(z1 - z0, 2));

    // Output the calculation of the straight-line distance
    qDebug() << "Calculating 3D distance:";
    qDebug() << "x1 - x0 =" << x1 - x0 << ", y1 - y0 =" << y1 - y0 << ", z1 - z0 =" << z1 - z0;
    qDebug() << "distance3D = sqrt(" << std::pow(x1 - x0, 2) << " + "
             << std::pow(y1 - y0, 2) << " + "
             << std::pow(z1 - z0, 2) << ") = " << distance3D;

    // Calculate the distance ratio
    float ratio = distance / distance3D;

    // Output the calculation of the ratio
    qDebug() << "Calculating ratio:";
    qDebug() << "ratio = distance / distance3D = " << distance << " / " << distance3D << " = " << ratio;

    // Calculate the target coordinates
    Point point;
    point.x = x0 + (x1 - x0) * ratio;
    point.y = y0 + (y1 - y0) * ratio;
    point.z = z0 + (z1 - z0) * ratio;

    // Output the calculation of the target coordinates
    qDebug() << "Calculating target coordinates:";
    qDebug() << "point.x = x0 + (x1 - x0) * ratio = " << x0 << " + (" << x1 << " - " << x0 << ") * " << ratio << " = " << point.x;
    qDebug() << "point.y = y0 + (y1 - y0) * ratio = " << y0 << " + (" << y1 << " - " << y0 << ") * " << ratio << " = " << point.y;
    qDebug() << "point.z = z0 + (z1 - z0) * ratio = " << z0 << " + (" << z1 << " - " << z0 << ") * " << ratio << " = " << point.z;

    return point;
}



bool gCodeModulation::deleteRemoteFile(const QString& workPiece) {


    if (!isHostOnline("192.168.1.88")) {
        qDebug() << "目标主机不可达";
        return false;
    }

    QString remotePath = "./PlcLogic/_cnc/" + workPiece + ".cnc";
    std::string remotePathStr = remotePath.toStdString();
    const char* remoteFilePath = remotePathStr.c_str();

    const char* hostname = "192.168.1.88";
    const char* username = "update";
    const char* password = "123456";

    WSADATA wsadata;
    if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return false;
    }

    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return false;
    }

    sockaddr_in sin{};
    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);  // SFTP默认端口

    // Windows下用 InetPtonA 替代 inet_pton
    if (InetPtonA(AF_INET, hostname, &sin.sin_addr) != 1) {
        std::cerr << "InetPtonA failed.\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    // 用全局命名空间调用 connect，避免和 Qt connect 冲突
    if (::connect(sock, (struct sockaddr*)&sin, sizeof(sin)) != 0) {
        std::cerr << "Failed to connect.\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    LIBSSH2_SESSION* session = libssh2_session_init();
    if (!session) {
        std::cerr << "Failed to init SSH session.\n";
        closesocket(sock);
        WSACleanup();
        return false;
    }

    if (libssh2_session_handshake(session, sock)) {
        std::cerr << "SSH session handshake failed.\n";
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        return false;
    }

    if (libssh2_userauth_password(session, username, password)) {
        std::cerr << "Authentication failed.\n";
        libssh2_session_disconnect(session, "Bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        return false;
    }

    LIBSSH2_SFTP* sftp_session = libssh2_sftp_init(session);
    if (!sftp_session) {
        std::cerr << "Unable to init SFTP session.\n";
        libssh2_session_disconnect(session, "Bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        return false;
    }

    int rc = libssh2_sftp_unlink(sftp_session, remoteFilePath);
    if (rc != 0) {
        std::cerr << "Failed to delete file: " << remoteFilePath << "\n";
        libssh2_sftp_shutdown(sftp_session);
        libssh2_session_disconnect(session, "Bye");
        libssh2_session_free(session);
        closesocket(sock);
        WSACleanup();
        return false;
    }

    std::cout << "File deleted successfully: " << remoteFilePath << "\n";

    libssh2_sftp_shutdown(sftp_session);
    libssh2_session_disconnect(session, "Bye");
    libssh2_session_free(session);
    closesocket(sock);
    WSACleanup();

    return true;
}
