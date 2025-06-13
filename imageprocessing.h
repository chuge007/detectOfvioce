#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QWidget>

namespace Ui {
class ImageProcessing;
}

class ImageProcessing : public QWidget
{
    Q_OBJECT

public:
    explicit ImageProcessing(QWidget *parent = nullptr);
    ~ImageProcessing();

private:
    Ui::ImageProcessing *ui;
};

#endif // IMAGEPROCESSING_H
