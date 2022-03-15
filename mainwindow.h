#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QLabel;
QT_END_NAMESPACE

// for working with SVG files
class SvgView;

// color options for gray scylr procesing
enum ColorOption {GrayColor, PinkColor, BlueColor};

// option change color scale options
enum ColorScale {RedScale, GreenScale, BlueScale};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /// <***
    /// Function on_loadFirstImageButton_clicked event handler wich called loadImage function with first control parametr
    /// ***>
    void on_loadFirstImageButton_clicked();

    /// <***
    /// Function on_loadFirstImageButton_clicked event handler wich called loadImage function with first control parametr
    /// ***>
    void on_LoadSecondImageButton_clicked();

    /// <***
    /// Function on_processingImagesButton_clicked processing first and second image and show result
    /// ***>
    void on_processingImagesButton_clicked();

    /// <***
    /// Function on_loadFirstSvgImageButton_clicked load SVG Image in local variable firstSvgView
    /// ***>
    void on_loadFirstSvgImageButton_clicked();

    /// <***
    /// Function on_loadFirstSvgImageButton_clicked load SVG Image in local variable secondSvgView
    /// ***>
    void on_loadSecondSvgImageButton_clicked();

    /// <***
    /// Function on_loadRGBImageButton_clicked load RGB Image in second TabPage "Color scale image processing"
    /// and enable components
    /// ***>
    void on_loadRGBImageButton_clicked();

    /// <***
    /// Function on_redColorVerticalSlider_valueChanged event handler change value control redColorVerticalSlider in second TabPage "Color scale image processing"
    /// and processing RGB image in red byte
    /// ***>
    void on_redColorVerticalSlider_valueChanged(int value);

    /// <***
    /// Function on_greenColorVerticalSlider_valueChanged event handler change value control greenColorVerticalSlider in second TabPage "Color scale image processing"
    /// and processing RGB image in red byte
    /// ***>
    void on_greenColorVerticalSlider_valueChanged(int value);

    /// <***
    /// Function on_blueColorVerticalSlider_valueChanged event handler change value control blueColorVerticalSlider in second TabPage "Color scale image processing"
    /// and processing RGB image in red byte
    /// ***>
    void on_blueColorVerticalSlider_valueChanged(int value);

    /// <***
    /// Function processingGrayscaleResultImage change current tab page "Composition Image processing" to next tab page "Color Image Processing"
    /// and assign values controls resultPage in current tab page into values controls next page
    /// ***>
    void processingGrayscaleResultImage();

    /// <***
    /// Function enableColorModeControls enabled ColorMode Controls into tab page "Color Image Processing"
    /// ***>
    void enableColorModeControls();

    /// <***
    /// Function on_processingColorImageButton_clicked processing RGB image in second TabPage "Color scale image processing"
    /// ***>
    void on_processingColorImageButton_clicked();

    /// <***
    /// Function on_processingSvgImagesButton_clicked processing SVG images in thrid TabPage "SVG images processing"
    /// ***>
    void on_processingSvgImagesButton_clicked();

private:
    // Image for composition processing in first Tab page
    QImage firstImage;
    QImage secondImage;
    QImage resultImage;

    // Image for greyscale processing in second Tab page
    QImage rgbImage;
    QImage grayscaleImage;

    // Image for SVG processing in third Tab page
    SvgView *firstSvgView;
    SvgView *secondSvgView;

    // new window
    QWidget *newWindowWidget = NULL;

    Ui::MainWindow *ui;

    /// <***
    /// Function currentMode determinate what composition mode was selected
    /// ***>
    QPainter::CompositionMode currentMode();

    /// <***
    /// Function loadImage load Image from dialog box into window and return full pathname with filename
    /// loaded image in control which was obtained using parameter *label
    /// loaded image in local variable firstImage or secondImage which was obtained using parameter *image
    /// ***>
    void loadImage(QLabel *label, QImage *image);

    /// <***
    /// Function checkResultImagesProcessingEnable check if firstImage and secondImage loaded
    /// then set enable processing options controls
    /// ***>
    void checkLoadingImages();

    /// <***
    /// Function checkLoadingSvgImages check if firstImage and second SVG Images loaded
    /// then set enable SVG processing options controls
    /// ***>
    void checkLoadingSvgImages();

    /// <***
    /// Function processingImageColorSlider called event handlers on_...ColorSlider_valueChanged for processing
    /// ***>
    void processingImageColorSlider(ColorScale colorScale, int value);

    /// <***
    /// Function openSeparateWindows processing RGB image
    /// and create new window and show result color image and grayScale image
    /// ***>
    void openSeparateWindows();

    /// <***
    /// Function setProportionalSize set proportional Size in control QLabel
    /// ***>
    void setProportionalSize(QLabel *label, QImage image);

};

#endif // MAINWINDOW_H
