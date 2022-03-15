#ifndef COMPOSITIONPROCESSING_H
#define COMPOSITIONPROCESSING_H

#include <QMainWindow>
#include <QPainter>

#include "ImageProcessing.h"

// class for CompositionProcessing
class CompositionProcessing : public ImageProcessing
{
public:
    //CompositionProcessing() {};
    CompositionProcessing(QImage firstImageParam, QImage secondImageParam, QPainter::CompositionMode modeParam)
        : firstImage(firstImageParam), secondImage(secondImageParam), mode(modeParam) {};
    ~CompositionProcessing() {};

    /// <*
    /// method implemented derived method Procesing which processing RGB image and return Grayscale image
    /// *>
    virtual QImage Processing() override;

private:
    QImage firstImage;
    QImage secondImage;
    //QImage resultImage;

    QPainter::CompositionMode mode;
};

#endif // COMPOSITIONPROCESSING_H
