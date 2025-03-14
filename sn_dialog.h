#ifndef SN_DIALOG_H
#define SN_DIALOG_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class SN_Dialog;
}

class SN_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit SN_Dialog(QWidget *parent = 0);
    ~SN_Dialog();
    QString get_SN();
    void mkeyPressEvent(QKeyEvent *event){keyPressEvent(event);}

private slots:
    void on_ok_but_clicked();
    void press(void);
    void on_cancel_but_clicked();

private:
    Ui::SN_Dialog *ui;
protected:
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // SN_DIALOG_H
