
#include "GreyScaleProcessing.h"

QImage GreyScaleProcessing::Processing()
{
    // copy RGB image in temp image for processing
    QImage image = sourceImage;

    // change in array image each RGB pixel to Grayscale pixel
    for (int countX = 0; countX < image.width(); countX++)
        for (int countY = 0; countY < image.height(); countY++)
        {
//            // get pixel and convert it to gray color
//            int grayColor = qGray(image.pixel(countX, countY));
//            // set gray pixel
//            image.setPixel(countX, countY, QColor(grayColor, grayColor, grayColor).rgb());

            // get pixel
            QRgb sourcePixel= image.pixel(countX, countY);

            // get gray color value
            unsigned char grayColorValue = qGray(sourcePixel);

            // set gray color
            QColor color = QColor(grayColorValue, grayColorValue, grayColorValue);

            // set gray pixel
            QRgb resultPixel = color.rgb();

            // get double value
            double value = double(resultPixel);

            //set pixel
            image.setPixel(countX, countY, value);

        }

    // return processing grayscale image
    return image;
}

QImage GreyScaleProcessing::ProcesingLowLevel(ColorOption colorOption)
{
    // get format image
    //QImage::Format formatImage = currentImage.format();

    // copy RGB image in temp image for processing
    QImage image = sourceImage;

    int pixelSize = QImage::Format_RGB32;

    // determinated image size
    int size = getImageSize(image, pixelSize);

    // load data from image into std::vector
    std::vector<unsigned char> data = getByteData(image, pixelSize);

    // change in array image each RGB pixel to Grayscale pixel
    for ( int count = 0; count < size; count += pixelSize )
    {
        // read red, green and blue value from array
        unsigned char b = data[count];
        unsigned char g = data[count + 1];
        unsigned char r = data[count + 2];
        //unsigned char w = data[count + 3];
        switch(colorOption)
        {
            case ColorOption::GrayColor :
            {
                // get shades gray
                //unsigned char grayColor = (r*11 + g*16 + b*5) / 32;
                unsigned char grayColor = (r*12 + g*12 + b*8) / 32;

                // assign value gray red, green and blue bites
                data[count] = grayColor;
                data[count + 1] = grayColor;
                data[count + 2] = grayColor;
            }
            break;
            // pink effect
            case ColorOption::PinkColor :
            {
                //*((uint16_t *) (data + count)) = (r*11+g*16+b*5)/32;

                // assign only green byte minimal value
                data[count + 1] = data[count + 1] >> 8 | 0x1;
            }
            break;
            // blue effect
            case ColorOption::BlueColor :
            {
                //*((uint32_t *) (data + count)) = (r*11+g*16+b*5)/32;

                // assign only blue byte mamximum value = 255
                data[count] = (data[count] >> 8) | 0xff;
                // dicreasy values green bytes not so big
                data[count + 1] = data[count + 1] >> 0x1;
                // dicreasy values red byte more
                data[count + 2] = data[count + 2] >> 0x2;
            }
            break;
        }
    }

    // copy processing image
    unsigned char *data_ptr = new unsigned char[size];
    std::copy(data.data(), data.data() + size, data_ptr);
    auto data_schared_ptr = std::make_shared<unsigned char*>(data_ptr);

    QImage res_image = QImage(data_ptr, image.width(), image.height(), QImage::Format_RGB32);

    // return processing grayscale image
    return res_image;

}

QImage GreyScaleProcessing::ProcesingRGB(QImage currentImage, ColorScale colorScale, int value)
{
    // copy RGB image in temp image for processing
    QImage image = currentImage;

    // change in array image each RGB pixel
    for (int countX = 0; countX < image.width(); countX++)
        for (int countY = 0; countY < image.height(); countY++)
        {
            // get pixel and convert it to gray color
            QColor pixelColor = QColor(image.pixel(countX, countY));
            // set color pixel
            switch(colorScale)
            {
                case ColorScale::RedScale :
                    image.setPixel(countX, countY, QColor(value, pixelColor.green(), pixelColor.blue()).rgb());
                    break;
                case ColorScale::GreenScale :
                    image.setPixel(countX, countY, QColor(pixelColor.red(), value, pixelColor.blue()).rgb());
                    break;
                case ColorScale::BlueScale :
                    image.setPixel(countX, countY, QColor(pixelColor.red(), pixelColor.green(), value).rgb());
                    break;
            }
        }

    return image;
}

//unsigned char* GreyScaleProcessing::getByteData(QImage image, int pixelSize)
std::vector<unsigned char> GreyScaleProcessing::getByteData(QImage image, int pixelSize)
{
    int size = getImageSize(image, pixelSize);

    // create std vector
    std::vector<unsigned char> data;

    // copy data from image
    std::copy(image.constBits(), image.constBits() + size, back_inserter(data));

    return data;
}

int GreyScaleProcessing::getImageSize(QImage image, int pixelSize)
{
    return image.width() * image.height() * pixelSize;
}
