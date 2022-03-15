
#include "CompositionProcessing.h"

QImage CompositionProcessing::Processing()
{
    // get local variable copy images for scaling and processing
    QImage _firstImage;
    QImage _secondImage;

    // calculate what image have more width and set this image first
    if( firstImage.width() < secondImage.width() )
    {
        _firstImage = secondImage;
        _secondImage = firstImage;
    }
    else
    {
        _firstImage = firstImage;
        _secondImage = secondImage;
    }

    QImage resultImage = QImage(_firstImage.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&resultImage);

    // prepare second image for composition
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    // calculate maximal height
    int maxHeigt = ( _firstImage.height() < _secondImage.height() ) ? _secondImage.height() : _firstImage.height();
    // calculate maximal width
    int maxWidth = ( _firstImage.width() < _secondImage.width() ) ? _secondImage.width() : _firstImage.width();

    // scale image with max width and height
    _secondImage =_secondImage.scaled(maxHeigt, maxWidth, Qt::KeepAspectRatio); //IgnoreAspectRatio
    //_secondImage =_secondImage.scaledToWidth(maxHeigt);
    //_secondImage =_secondImage.scaledToHeight(minHeigt);

    painter.drawImage(0, 0,_secondImage);

    // load first image for composition
    painter.setCompositionMode(mode);
    painter.drawImage(0, 0, _firstImage);

    painter.end();

    return resultImage;
}
