#include "gcodemodulation.h"
#include "ui_gcodemodulation.h"
#include "mainwindow.h"

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

    connect(ui->pbAganStart, &QPushButton::clicked, MainWindow::scanDetectCtrl, &ScanControlAbstract::on_xSubBtn_released);

    gcodePath="C:/ProgramData/CODESYS/Simulation/PlcLogic/";
    filePath=gcodePath+"1.cnc";
}



gCodeModulation::~gCodeModulation()
{
    delete ui;
}

void gCodeModulation::loadGCodeToPlainText()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(nullptr, QString::fromLocal8Bit("提示"),
                                  QString::fromLocal8Bit("是否重新加载未更改数据？"),
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
    QSpinBox *valueBox = new QSpinBox;
    QPushButton *deleteBtn = new QPushButton(QString::fromLocal8Bit("删除"));

    rowWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    rowWidget->setMinimumHeight(30);
    rowLayout->setContentsMargins(4, 2, 4, 2);
    rowLayout->setSpacing(8);

    minBox->setRange(0, 1000);
    maxBox->setRange(0, 1000);
    valueBox->setRange(0, 1000);



    rowLayout->addWidget(new QLabel(QString::fromLocal8Bit("范围:")));
    rowLayout->addWidget(minBox);
    rowLayout->addWidget(new QLabel("~"));
    rowLayout->addWidget(maxBox);
    rowLayout->addWidget(new QLabel(QString::fromLocal8Bit("值:")));
    rowLayout->addWidget(valueBox);
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
    row.valueBox = valueBox;
    rangeRows.append(row);
}






void gCodeModulation::on_saveBtn_clicked()
{
    savedRanges.clear();

    for (const auto& row : rangeRows) {
        int minVal = row.minBox->value();
        int maxVal = row.maxBox->value();
        int val    = row.valueBox->value();

        // 可选：校验
        if (minVal > maxVal) std::swap(minVal, maxVal);

        savedRanges.append({minVal, maxVal, val});
    }



    QStringList lines = ui->pTEgcode->toPlainText().split('\n');


    QStringList out;
    QRegularExpression cmdRe("\\b(G0[123])\\b");  // 匹配 G01、G02、G03

    for (const QString& line : lines) {
        QString trimmedLine = line.trimmed();
        QRegularExpressionMatch cmdMatch = cmdRe.match(trimmedLine);

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

            } else {
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
                int speed   = getValueByRange(static_cast<int>(radius));

                QString newLine = trimmedLine +
                    QString(" F%1 E%2 E-%3")
                        .arg(speed)
                        .arg(ui->dsbAccV->value())
                        .arg(ui->dsbAccV->value());
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



int gCodeModulation::getValueByRange(int input){
    for (const auto& r : savedRanges) {
        if (input >= r.minValue && input <= r.maxValue) {
            return r.assignedValue;
        }
    }


    return ui->dsbLineV->value();
}


double gCodeModulation::calculateRadius(double endX, double endY, double centerI, double centerJ)
{
    double centerX = endX + centerI;
    double centerY = endY + centerJ;
    return std::hypot(endX - centerX, endY - centerY);
}
