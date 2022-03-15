#include <QMainWindow>
#include <QPainter>

#include "mainwindow.h"

#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

// abstract base class ImageProcessing
class ImageProcessing
{
public:

    // clear virtual function processing image
    virtual QImage Processing() = 0;
};

#endif // IMAGEPROCESSING_H
