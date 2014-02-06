#include <QtGui>
#include "mainwindow.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    operationHistory.brightness = 0;
    operationHistory.contrast = 1;
    operationHistory.quantization = 256;

    createEditableImageSubWindow();
    createCentralWidget();
    createActions();
    createMenus();
    createDockWindows();

    setWindowTitle(tr("Image Processor"));
    resize(500, 400);
}

MainWindow::~MainWindow()
{
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save as..."), this);
    saveAct->setShortcut(tr("Ctrl+S"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    flipHorAct = new QAction(tr("Flip horizontal"), this);
    flipHorAct->setShortcut(tr("Ctrl+F+H"));
    connect(flipHorAct, SIGNAL(triggered()), this, SLOT(flipHorizontal()));

    flipVerAct = new QAction(tr("Flip vertical"), this);
    flipVerAct->setShortcut(tr("Ctrl+F+V"));
    connect(flipVerAct, SIGNAL(triggered()), this, SLOT(flipVertical()));

    luminanceAct = new QAction(tr("Luminance"), this);
    luminanceAct->setShortcut(tr("Ctrl+L"));
    connect(luminanceAct, SIGNAL(triggered()), this, SLOT(luminanceTransform()));

    negativeAct = new QAction(tr("Negative"), this);
    negativeAct->setShortcut(tr("Ctrl+N"));
    connect(negativeAct, SIGNAL(triggered()), this, SLOT(negativeTransform()));

    histEqualizationAct = new QAction(tr("Histogram equalization"), this);
    histEqualizationAct->setShortcut(tr("Ctrl+H+E"));
    connect(histEqualizationAct, SIGNAL(triggered()), this, SLOT(histEqualizationTransform()));

    rotateLeftAct = new QAction(tr("Rotate left"), this);
    rotateLeftAct->setShortcut(tr("Ctrl+R+L"));
    connect(rotateLeftAct, SIGNAL(triggered()), this, SLOT(rotateLeft()));

    rotateRightAct = new QAction(tr("Rotate right"), this);
    rotateRightAct->setShortcut(tr("Ctrl+R+R"));
    connect(rotateRightAct, SIGNAL(triggered()), this, SLOT(rotateRight()));

    clearAct = new QAction(tr("Clear transformations"), this);
    clearAct->setShortcut(tr("Ctrl+C+D"));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearTransformations()));
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    transformMenu = new QMenu(tr("&Transformation"), this);
    transformMenu->addAction(flipHorAct);
    transformMenu->addAction(flipVerAct);
    transformMenu->addAction(luminanceAct);
    transformMenu->addAction(negativeAct);
    transformMenu->addAction(histEqualizationAct);
    transformMenu->addAction(rotateLeftAct);
    transformMenu->addAction(rotateRightAct);
    transformMenu->addAction(clearAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(transformMenu);
}

void MainWindow::initComponentsState()
{
    quantizationWidget->initState();
    brightnessWidget->initState();
    contrastWidget->initState();
    zoomWidget->initState();
    convolutionWidget->initState();
}

void MainWindow::createOriginalImageSubWindow()
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
}

void MainWindow::createEditableImageSubWindow()
{
    imageLabelTwo = new QLabel;
    imageLabelTwo->setBackgroundRole(QPalette::Base);
    imageLabelTwo->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabelTwo->setScaledContents(true);

    scrollAreaTwo = new QScrollArea;
    scrollAreaTwo->setBackgroundRole(QPalette::Dark);
    scrollAreaTwo->setWidget(imageLabelTwo);
}

void MainWindow::createDockWindows()
{
    createOriginalImageSubWindow();

    QDockWidget *dock = new QDockWidget(tr("Original image"), this);
    dock->setMinimumWidth(300);
    dock->setMinimumHeight(300);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(scrollArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    dock = new QDockWidget(tr("Quantization"), this);
    dock->setWidget(quantizationWidget);
    dock->setMinimumWidth(200);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("Brightness"), this);
    dock->setWidget(brightnessWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("Contrast"), this);
    dock->setWidget(contrastWidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dockHistogram = new QDockWidget(tr("Histogram"), this);
    dockHistogram->setMinimumWidth(256);
    dockHistogram->setMinimumHeight(256);
    //dockHistogram->setWidget(hist);
    addDockWidget(Qt::LeftDockWidgetArea, dockHistogram);

    dock = new QDockWidget(tr("Zoom"), this);
    dock->setWidget(zoomWidget);
    dock->setMinimumHeight(150);
    addDockWidget(Qt::RightDockWidgetArea, dock);

    dock = new QDockWidget(tr("Convolution"), this);
    dock->setWidget(convolutionWidget);
    dock->setMinimumWidth(210);
    dock->setMinimumHeight(160);
    addDockWidget(Qt::RightDockWidgetArea, dock);
 }

void MainWindow::createCentralWidget()
{
    centralScrollArea = new QScrollArea;
    centralScrollArea->setBackgroundRole(QPalette::Dark);

    hLayout = new QHBoxLayout;
    hLayout->addWidget(scrollAreaTwo);

    centralScrollArea->setLayout(hLayout);
    setCentralWidget(centralScrollArea);

    createQuantizationWidget();
    createBrigthnessWidget();
    createContrastWidget();
    createZoomWidget();
    createConvolutionWidget();
}

void MainWindow::createQuantizationWidget()
{
    quantizationWidget = new QuantizationWidget;
    connect(quantizationWidget, SIGNAL(valueChanged(int)), this, SLOT(quantization(int)));
}

void MainWindow::createBrigthnessWidget()
{
    brightnessWidget = new BrightnessWidget;
    connect(brightnessWidget, SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
}

void MainWindow::createContrastWidget()
{
    contrastWidget = new ContrastWidget;
    connect(contrastWidget, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
}

void MainWindow::createZoomWidget()
{
    zoomWidget = new ZoomWidget;
    connect(zoomWidget, SIGNAL(zoomOut(int,int)), this, SLOT(zoomOut(int,int)));
    connect(zoomWidget, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
}

void MainWindow::createConvolutionWidget()
{
    convolutionWidget = new ConvolutionWidget;
    connect(convolutionWidget, SIGNAL(convolutionTriggered(QVector<qreal>)), this, SLOT(convolution(QVector<qreal>)));
}

//----------------------------------------------------
// slots
//----------------------------------------------------
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::information(this, tr("Image Processor"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        imageLabel->setPixmap(QPixmap::fromImage(image));
        imageLabelTwo->setPixmap(QPixmap::fromImage(image));

        /*scaleFactor = 1.0;

        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            imageLabel->adjustSize();*/

        imageLabel->adjustSize();
        imageLabelTwo->adjustSize();

        histogram();
        initComponentsState();
    }
}

void MainWindow::save()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage image = imageLabelTwo->pixmap()->toImage();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"));
    image.save(fileName, "jpg", 100);
}

void MainWindow::flipHorizontal()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::flipHorizontal(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::flipVertical()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::flipVertical(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::luminanceTransform()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::luminance(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
}

void MainWindow::negativeTransform()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::negative(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::histEqualizationTransform()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::histogramEqualization(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::quantization(int value)
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::quantization(imageLabel->pixmap()->toImage(), value);
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::histogram()
{
    hist = new QLabel;
    QImage histImage = Operation::histogram(imageLabelTwo->pixmap()->toImage());
    hist->setPixmap(QPixmap::fromImage(histImage));
    hist->setMargin(20);
    dockHistogram->setWidget(hist);
}

void MainWindow::brightness(int value)
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::brightness(imageLabel->pixmap()->toImage(), value);
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::contrast(int value)
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::contrast(imageLabel->pixmap()->toImage(), value);
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::zoomOut(int wVal, int hVal)
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::zoomOut(imageLabelTwo->pixmap()->toImage(), wVal, hVal);
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    imageLabelTwo->adjustSize();
    histogram();
}

void MainWindow::zoomIn()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::zoomIn(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    imageLabelTwo->adjustSize();
    histogram();
}

void MainWindow::rotateLeft()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::rotateLeft(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::rotateRight()
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::rotateRight(imageLabelTwo->pixmap()->toImage());
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::convolution(QVector<qreal> kernel)
{
    if (imageLabel->pixmap() == NULL)
        return;

    QImage newImage = Operation::convolution(imageLabelTwo->pixmap()->toImage(), kernel);
    imageLabelTwo->setPixmap(QPixmap::fromImage(newImage));
    histogram();
}

void MainWindow::clearTransformations()
{
    imageLabelTwo->setPixmap(QPixmap::fromImage(imageLabel->pixmap()->toImage()));
    imageLabelTwo->adjustSize();
    initComponentsState();
    histogram();
}
