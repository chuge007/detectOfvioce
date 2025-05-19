#ifndef ADDROUTE_DIALOG_H
#define ADDROUTE_DIALOG_H

#include <QDialog>

namespace Ui {
class addRoute_dialog;
}

class addRoute_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit addRoute_dialog(QWidget *parent = 0);
    ~addRoute_dialog();

    QList <QString>  getEndPos();
    QList <QString>  getStartPos();
    QList <QString>  getTransPos();
    QList <QString>  StartPos;
    void update_Ui(int state,QString xEnd,QString yEnd,QString z0,QString r0,
                   QString xTrans,QString yTrans,QString zTrans,QString rTrans );
    void closeEvent(QCloseEvent *event) override;

    bool isOpen=false;
private slots:
    void on_pushButton_accept();

    void on_pushButton_reject();

    void pbSetCurposToEndPos();

    void pbSetCurposToTransPos();

public slots:
    void set_Xcurpos(QString curX);
    void set_Ycurpos(QString curY);
    void set_Zcurpos(QString curZ);
    void set_Rcurpos(QString curR);

private:
    Ui::addRoute_dialog *ui;

signals:
    void addBut_x_pressed();
    void subBut_x_pressed();
    void addBut_y_pressed();
    void subBut_y_pressed();
    void addBut_z_pressed();
    void subBut_z_pressed();
    void addBut_r_pressed();
    void subBut_r_pressed();

    void addBut_x_released();
    void subBut_x_released();
    void addBut_y_released();
    void subBut_y_released();
    void addBut_r_released();
    void subBut_r_released();
    void subBut_z_released();
    void addBut_z_released();
};

#endif // ADDROUTE_DIALOG_H
