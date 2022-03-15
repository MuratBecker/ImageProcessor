#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QResizeEvent>

#include "svgview.h"
//#include "ImageProcessing.h"
#include "CompositionProcessing.h"
#include "GreyScaleProcessing.h"

//! [0]
static const QSize resultSize(1000, 800);
//! [0]


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , firstSvgView(new SvgView)
    , secondSvgView(new SvgView)
    , ui(new Ui::MainWindow)
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    // add item loadFirst in Menu and Toolbar
    //const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openFirstAct = new QAction(tr("&LoadFirst..."), this);
    openFirstAct->setShortcuts(QKeySequence::Open);
    openFirstAct->setStatusTip(tr("Load first image file"));
    connect(openFirstAct, &QAction::triggered, this, &MainWindow::on_loadFirstImageButton_clicked);
    fileMenu->addAction(openFirstAct);
    fileToolBar->addAction(openFirstAct);
    fileToolBar->addSeparator();

    // add item loadSecond in Menu and Toolbar
    QAction *openSecondAct = new QAction(tr("&LoadSecond..."), this);
    openSecondAct->setShortcuts(QKeySequence::Open);
    openSecondAct->setStatusTip(tr("Load second image file"));
    connect(openSecondAct, &QAction::triggered, this, &MainWindow::on_LoadSecondImageButton_clicked);
    fileMenu->addAction(openSecondAct);
    fileToolBar->addAction(openSecondAct);
    fileToolBar->addSeparator();
    fileMenu->addSeparator();

    // add item exit in Menu and Toolbar
    const QIcon exitIcon = QIcon::fromTheme("application-exit");
    QAction *exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    fileMenu->addAction(exitAct);
    fileToolBar->addAction(exitAct);

    // init resultImage
    resultImage = QImage(resultSize, QImage::Format_ARGB32_Premultiplied);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*******************************************************************************************
*** the beginning of the code block of the FIRST Tab page "Composition Image processing" ***
************************************************************************************+*******/

/// function setProportionalSize set control label proportional size
void MainWindow::setProportionalSize(QLabel *label, QImage image)
{
    // set proportional size
    QSize pixSize = image.size();

    pixSize.scale(label->size(), Qt::KeepAspectRatio);
    //pixSize.scale(label->size(), Qt::KeepAspectRatioByExpanding);

    label->setFixedSize(pixSize);
    label->setScaledContents(true);
}

void MainWindow::checkLoadingImages()
{
    if( !ui->firstImageLabel->pixmap().isNull() && !ui->secondImageLabel->pixmap().isNull() )
    {
       ui->processingOptionsGroupBox->setEnabled(true);
       ui->processingOptionsFrame->setEnabled(true);
       ui->processingImagesButton->setEnabled(true);
       ui->processingImagesButton->setToolTip("Select composite mode in panel \"Processing Options\" and click this button for processing first and second images");
    }
}

void MainWindow::loadImage(QLabel *label, QImage *image)
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select image",":/images/");
    if (!fileName.isEmpty())
    {
        QPixmap pm(fileName);
        // show image in control
        //label->setPixmap(pm.scaledToWidth(pm.size().width(), Qt::SmoothTransformation));
        label->setPixmap(pm);

        // load first or second image
        image->load(fileName);

        // set proportional size
        setProportionalSize(label, *image);

        if( ui->processingImagesButton->isEnabled() )
            on_processingImagesButton_clicked();

        // if both images loaded, set enable processing options controls
        checkLoadingImages();
    }
}

void MainWindow::on_loadFirstImageButton_clicked()
{
      loadImage(ui->firstImageLabel, &firstImage);
}

void MainWindow::on_LoadSecondImageButton_clicked()
{
      loadImage(ui->secondImageLabel, &secondImage);
}

void MainWindow::on_processingImagesButton_clicked()
{
    // using class CompositionProcessing derived from ImageProcessing abstract class
    CompositionProcessing compositionProcessing(firstImage, secondImage, currentMode());
    // apply composition processing
    resultImage = compositionProcessing.Processing();

    // show result image after processing
    ui->resultImageLabel->setPixmap(QPixmap::fromImage(resultImage));
    //ui->resultImageLabel->setScaledContents(true);

    // set proportional size
    setProportionalSize(ui->resultImageLabel, resultImage);

    if( ui->grayScaleCheckBox->isChecked() )
        processingGrayscaleResultImage();
}

QPainter::CompositionMode MainWindow::currentMode()
{
    QPainter::CompositionMode mode = QPainter::CompositionMode_SourceOver;
    if (ui->radioButton1->isChecked())
        mode = QPainter::CompositionMode_SourceOver;
    else if (ui->radioButton2->isChecked())
        mode = QPainter::CompositionMode_DestinationOver;
    else if (ui->radioButton3->isChecked())
        mode =  QPainter::CompositionMode_Difference;
    else if (ui->radioButton4->isChecked())
        mode =  QPainter::CompositionMode_Clear;
    else if (ui->radioButton5->isChecked())
        mode =  QPainter::CompositionMode_Source;
    else if (ui->radioButton6->isChecked())
        mode =  QPainter::CompositionMode_Destination;
    else if (ui->radioButton7->isChecked())
        mode =  QPainter::CompositionMode_SourceIn;
    else if (ui->radioButton8->isChecked())
        mode =  QPainter::CompositionMode_DestinationIn;
    else if (ui->radioButton9->isChecked())
        mode =  QPainter::CompositionMode_SourceAtop;
    else if (ui->radioButton10->isChecked())
        mode =  QPainter::CompositionMode_DestinationAtop;
    else if (ui->radioButton11->isChecked())
        mode =  QPainter::CompositionMode_Xor;
    else if (ui->radioButton12->isChecked())
        mode =  QPainter::CompositionMode_Plus;
    else if (ui->radioButton13->isChecked())
        mode =  QPainter::CompositionMode_Multiply;
    else if (ui->radioButton14->isChecked())
        mode =  QPainter::CompositionMode_Screen;
    else if (ui->radioButton15->isChecked())
        mode =  QPainter::CompositionMode_Overlay;
    else if (ui->radioButton16->isChecked())
        mode =  QPainter::CompositionMode_Darken;
    else if (ui->radioButton17->isChecked())
        mode =  QPainter::CompositionMode_Lighten;
    else if (ui->radioButton18->isChecked())
        mode =  QPainter::CompositionMode_ColorDodge;
    else if (ui->radioButton19->isChecked())
        mode =  QPainter::CompositionMode_ColorBurn;
    else if (ui->radioButton20->isChecked())
        mode =  QPainter::CompositionMode_HardLight;
    else if (ui->radioButton21->isChecked())
        mode =  QPainter::CompositionMode_SoftLight;
    else if (ui->radioButton22->isChecked())
        mode =  QPainter::CompositionMode_Difference;
    else if (ui->radioButton23->isChecked())
        mode =  QPainter::CompositionMode_Exclusion;
    return mode;
}

/*******************************************************************************************
*** the beginning of the code block of the SECOND Tab page  "Grayscale image processing" ***
***************************************************************+****************************/

/// enable color mode controls
void MainWindow::enableColorModeControls()
{
    // enable ColorMode Controls
    ui->colorOptionsGroupBox->setEnabled(true);
    ui->colorModeFrame->setEnabled(true);
    ui->grayRadioButton->setEnabled(true);
    ui->pinkRadioButton->setEnabled(true);
    ui->blueRadioButton->setEnabled(true);
    ui->separateWindowCheckBox->setEnabled(true);
    ui->processingColorImageButton->setEnabled(true);
    ui->rgbScaleFrame->setEnabled(true);
    ui->redColorVerticalSlider->setEnabled(true);
    ui->greenColorVerticalSlider->setEnabled(true);
    ui->blueColorVerticalSlider->setEnabled(true);
}

void MainWindow::on_loadRGBImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select RGB image",":/images/");
    if (!fileName.isEmpty())
    {
        // show RGB image in window
        QPixmap pm(fileName);
        ui->rgbImageLabel->setPixmap(pm);
        //ui->rgbImageLabel->setScaledContents(true);

        // load RGB image in QImage type variable for processing
        rgbImage.load(fileName);

        // set proportional size
        setProportionalSize(ui->rgbImageLabel, rgbImage);


        // enable ColorMode controls
        enableColorModeControls();
    }
}

void MainWindow::openSeparateWindows()
{
    // create new window
    if (newWindowWidget != NULL)
        delete newWindowWidget;
    newWindowWidget = new QWidget;

    // create image label1
    QLabel *imageLabel1 = new QLabel();
    imageLabel1->setMinimumWidth(resultSize.width());

    // create image label2
    QLabel *imageLabel2 = new QLabel();
    imageLabel2->setMinimumWidth(resultSize.width());

    // create GreyScaleProcessing class, which derived ImageProcessing abstract class
    // which performs grayscale processing
    GreyScaleProcessing grayscaleProcessing(rgbImage);
    QImage grayImage;
    // processing with using options Gray, Red or Green radio buttons
    if (ui->grayRadioButton->isChecked())
        grayImage = grayscaleProcessing.ProcesingLowLevel(ColorOption::GrayColor);
    else if (ui->pinkRadioButton->isChecked())
        grayImage = grayscaleProcessing.ProcesingLowLevel(ColorOption::PinkColor);
    else if (ui->blueRadioButton->isChecked())
        grayImage = grayscaleProcessing.ProcesingLowLevel(ColorOption::BlueColor);

    //load processed greyscaled image in control
    imageLabel1->setPixmap(QPixmap::fromImage(rgbImage));
    imageLabel1->setScaledContents(true);

    //load processed greyscaled image in control
    imageLabel2->setPixmap(QPixmap::fromImage(grayImage));
    imageLabel2->setScaledContents(true);

    // add controls to new image
    auto *layout = new QHBoxLayout; // QGridLayout, QVBoxLayout, QFormLayout
    layout->setContentsMargins(0, 0, 0, 0); // no borders
    layout->addWidget(imageLabel1);
    layout->addWidget(imageLabel2);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setAlignment(Qt::AlignHorizontal_Mask);

    newWindowWidget->setLayout(layout);

    // open new window
    newWindowWidget->show();
}

void MainWindow::processingImageColorSlider(ColorScale colorScale, int value)
{
    // create GreyScaleProcessing class, which derived from ImageProcessing abstract class
    GreyScaleProcessing grayscaleProcessing(rgbImage);
    // processing Image with RGB options
    grayscaleImage = grayscaleProcessing.ProcesingRGB(rgbImage, colorScale, value);

    //load processed greyscaled image in control
    ui->grayscaleImageLabel->setPixmap(QPixmap::fromImage(grayscaleImage));
    ui->grayscaleImageLabel->setScaledContents(true);
}

void MainWindow::on_redColorVerticalSlider_valueChanged(int value)
{
    processingImageColorSlider(ColorScale::RedScale, value);
}

void MainWindow::on_greenColorVerticalSlider_valueChanged(int value)
{
    processingImageColorSlider(ColorScale::GreenScale, value);
}

void MainWindow::on_blueColorVerticalSlider_valueChanged(int value)
{
    processingImageColorSlider(ColorScale::BlueScale, value);
}

void MainWindow::processingGrayscaleResultImage()
{
    // switch to next tab page
    ui->tabWidget->setCurrentIndex(1);

    // assign values resultImage controls current page to values controls next page
    rgbImage = resultImage;
    // show result image after processing
    ui->rgbImageLabel->setPixmap(QPixmap::fromImage(rgbImage));
    //ui->rgbImageLabel->setScaledContents(true);

    // set proportional size
    setProportionalSize(ui->rgbImageLabel, rgbImage);

    // enable ColorMode controls
    enableColorModeControls();

    // apply grayscale processing
    on_processingColorImageButton_clicked();
}

void MainWindow::on_processingColorImageButton_clicked()
{
    // create GreyScaleProcessing class, which derived ImageProcessing abstract class
    // which performs grayscale processing
    GreyScaleProcessing grayscaleProcessing(rgbImage);
    //QImage grayImage;
    // low level processing with using options Gray, Red or Green radio buttons
    if (ui->grayRadioButton->isChecked())
        grayscaleImage = grayscaleProcessing.ProcesingLowLevel(ColorOption::GrayColor);
        //grayscaleImage = grayscaleProcessing.Processing();
    else if (ui->pinkRadioButton->isChecked())
        grayscaleImage = grayscaleProcessing.ProcesingLowLevel(ColorOption::PinkColor);
    else if (ui->blueRadioButton->isChecked())
        grayscaleImage = grayscaleProcessing.ProcesingLowLevel(ColorOption::BlueColor);
    // processing RGB image with using QT graphics library
    //grayscaleImage = grayscaleProcessing.Processing();

    //load processed greyscaled image in control
    ui->grayscaleImageLabel->setPixmap(QPixmap::fromImage(grayscaleImage));
    //ui->grayscaleImageLabel->setScaledContents(true);

    // set proportional size
    setProportionalSize(ui->grayscaleImageLabel, grayscaleImage);

    // show new window
    if( ui->separateWindowCheckBox->isChecked() )
        openSeparateWindows();
}

/****************************************************************************************
******* the beginning of the code block of the THIRD Tab page "SVG Image processing" ***
***************************************************************+*************************/

/// check Loading svg image
void MainWindow::checkLoadingSvgImages()
{
    if( ui->firstWidget->layout() != NULL && ui->secondWidget->layout() != NULL )
    {
       ui->processingSvgOptionsGroupBox->setEnabled(true);
       ui->processingSvgImagesButton->setEnabled(true);
       ui->processingSvgImagesButton->setToolTip("Click this button for processing first and second images");
    }
}

void MainWindow::on_loadFirstSvgImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select image",":/images/");
    if (!fileName.isEmpty())
    {
        // open file in add it to scene
        firstSvgView->openFile(fileName);

        // create layout for first widget
        auto layout = new QVBoxLayout(centralWidget());
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(firstSvgView);

        //add layout into first widgets
        ui->firstWidget->setLayout(layout);

        // if loaded first and second svg file enable result button and options
        checkLoadingSvgImages();
    }
}

void MainWindow::on_loadSecondSvgImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Select image",":/images/");
    if (!fileName.isEmpty())
    {
        // open file in add it to scene
        secondSvgView->openFile(fileName);

        // create layout for second widget
        auto layout = new QVBoxLayout(centralWidget());
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(secondSvgView);

        //add layout into second widget
        ui->secondWidget->setLayout(layout);

        // if loaded first and second svg file enable result button and options
        checkLoadingSvgImages();
    }
}

void MainWindow::on_processingSvgImagesButton_clicked()
{
    // add first and secons Sgg items to scene
    CompositionSvgView *resultSvgView = new CompositionSvgView();
    resultSvgView->loadSvgItems(firstSvgView, secondSvgView);

    // create layout for result widget
    auto layout = new QVBoxLayout(centralWidget());
    layout->setContentsMargins(0, 0, 0, 0);

    //add layout into result widget
    layout->addWidget(resultSvgView);
    ui->resultSvgWidget->setLayout(layout);
}

