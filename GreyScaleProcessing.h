#ifndef GREYSCALEPROCESSING_H
#define GREYSCALEPROCESSING_H

#include <QMainWindow>
#include <QPainter>

#include "ImageProcessing.h"

// class for greyscale image processing
class GreyScaleProcessing : public ImageProcessing
{
public:
    GreyScaleProcessing(QImage sourceImageParam)
        : sourceImage(sourceImageParam) {};
    ~GreyScaleProcessing() {};

    /// <***
    /// Function Procesing get RGB image and return Grascale image
    /// ***>
    QImage Processing() override;

    /// <***
    /// Function ProcesingLowLevel get RGB image and return Grascale image
    /// , parameter "colorOption"
    /// is option gray, red or blue color
    /// ***>
    QImage ProcesingLowLevel(ColorOption colorOption);

    /// <***
    /// Function grayscaleProcesingRGB processing RGB image with dependeces of parameter ColorScale and value
    /// , parameter "colorScale"
    /// Select what color scale would be changed.
    /// , parameter "value"
    /// contain value red, green or blue byte
    /// ***>
    QImage ProcesingRGB(QImage currentImage, ColorScale colorScale, int value);

private:
    QImage sourceImage;
    //QImage resultImage;

    /// <***
    /// Function getByteData get unsigned char* array from QImage for low level processing
    /// , parameter "sizePixel"
    /// is a size Pixel
    /// ***>
    //unsigned char* getByteData(QImage image, int sizePixel);
    std::vector<unsigned char>  getByteData(QImage image, int sizePixel);

    /// <***
    /// Function getImageSize get size of image
    /// , parameter "sizePixel"
    /// is a size Pixel
    /// ***>
    int getImageSize(QImage image, int pixelSize);

};

#endif // GREYSCALEPROCESSING_H
