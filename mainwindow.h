#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "operation.h"
#include "quantizationwidget.h"
#include "brightnesswidget.h"
#include "contrastwidget.h"
#include "zoomwidget.h"
#include "convolutionwidget.h"

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QHBoxLayout;
class QSpinBox;
class QListWidget;
class QSlider;
class QLineEdit;
QT_END_NAMESPACE


struct OperationHistory
{
    int quantization;
    int brightness;
    int contrast;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

//----------------------------------------------------
// signals
//----------------------------------------------------

//----------------------------------------------------
// methods
//----------------------------------------------------
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void createActions();
    void createMenus();
    void createOriginalImageSubWindow();
    void createEditableImageSubWindow();
    void createDockWindows();
    void createCentralWidget();
    void createQuantizationWidget();
    void createBrigthnessWidget();
    void createContrastWidget();
    void createZoomWidget();
    void createConvolutionWidget();
    void initComponentsState();

//----------------------------------------------------
// slots
//----------------------------------------------------
private slots:
    void open();
    void save();
    void flipHorizontal();
    void flipVertical();
    void luminanceTransform();
    void negativeTransform();
    void histogram();
    void histEqualizationTransform();
    void quantization(int value);
    void brightness(int value);
    void contrast(int value);
    void zoomOut(int wVal, int hVal);
    void zoomIn(); //2x
    void rotateLeft();
    void rotateRight();
    void convolution(QVector<qreal> kernel);
    void clearTransformations();

//----------------------------------------------------
// members
//----------------------------------------------------
private:
    QImage* originalImage;
    QLabel* imageLabel;
    QLabel* imageLabelTwo;
    QLabel* hist;
    QScrollArea* centralScrollArea;
    QScrollArea* scrollArea;
    QScrollArea* scrollAreaTwo;
    QuantizationWidget* quantizationWidget;
    BrightnessWidget* brightnessWidget;
    ContrastWidget* contrastWidget;
    ZoomWidget* zoomWidget;
    ConvolutionWidget* convolutionWidget;
    QHBoxLayout* hLayout;
    QAction* openAct;
    QAction* saveAct;
    QAction* exitAct;
    QAction* flipHorAct;
    QAction* flipVerAct;
    QAction* luminanceAct;
    QAction* negativeAct;
    QAction* histEqualizationAct;
    QAction* rotateLeftAct;
    QAction* rotateRightAct;
    QAction* clearAct;

    QMenu* fileMenu;
    QMenu* transformMenu;

    QDockWidget* dockHistogram;

    OperationHistory operationHistory;
};

#endif // MAINWINDOW_H
