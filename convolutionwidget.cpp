#include "convolutionwidget.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
ConvolutionWidget::ConvolutionWidget(QWidget *parent) :
    QScrollArea(parent)
{
    initComponents();
}

void ConvolutionWidget::initState()
{
    combo->setCurrentIndex(0);
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
void ConvolutionWidget::initComponents()
{
    combo = new QComboBox;
    connect(combo, SIGNAL(currentIndexChanged(int)), this, SLOT(comboChanged(int)));
    combo->setInsertPolicy(QComboBox::InsertAtBottom);
    initKernels();

    k11SpinBox = new QDoubleSpinBox;
    k11SpinBox->setDecimals(4);
    k11SpinBox->setRange(-16, 16);
    k12SpinBox = new QDoubleSpinBox;
    k12SpinBox->setDecimals(4);
    k12SpinBox->setRange(-16, 16);
    k13SpinBox = new QDoubleSpinBox;
    k13SpinBox->setDecimals(4);
    k13SpinBox->setRange(-16, 16);
    k21SpinBox = new QDoubleSpinBox;
    k21SpinBox->setDecimals(4);
    k21SpinBox->setRange(-16, 16);
    k22SpinBox = new QDoubleSpinBox;
    k22SpinBox->setDecimals(4);
    k22SpinBox->setRange(-16, 16);
    k23SpinBox = new QDoubleSpinBox;
    k23SpinBox->setDecimals(4);
    k23SpinBox->setRange(-16, 16);
    k31SpinBox = new QDoubleSpinBox;
    k31SpinBox->setDecimals(4);
    k31SpinBox->setRange(-16, 16);
    k32SpinBox = new QDoubleSpinBox;
    k32SpinBox->setDecimals(4);
    k32SpinBox->setRange(-16, 16);
    k33SpinBox = new QDoubleSpinBox;
    k33SpinBox->setDecimals(4);
    k33SpinBox->setRange(-16, 16);

    button = new QPushButton("Do convolution");
    connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

    layoutLine1 = new QHBoxLayout;
    layoutLine1->addWidget(k11SpinBox);
    layoutLine1->addWidget(k12SpinBox);
    layoutLine1->addWidget(k13SpinBox);

    layoutLine2 = new QHBoxLayout;
    layoutLine2->addWidget(k21SpinBox);
    layoutLine2->addWidget(k22SpinBox);
    layoutLine2->addWidget(k23SpinBox);

    layoutLine3 = new QHBoxLayout;
    layoutLine3->addWidget(k31SpinBox);
    layoutLine3->addWidget(k32SpinBox);
    layoutLine3->addWidget(k33SpinBox);

    layout = new QVBoxLayout;
    layout->addWidget(combo);
    layout->addLayout(layoutLine1);
    layout->addLayout(layoutLine2);
    layout->addLayout(layoutLine3);
    layout->addWidget(button);
    this->setLayout(layout);
}

void ConvolutionWidget::initKernels()
{
    QVector<qreal> blank;
    blank.append(0);
    blank.append(0);
    blank.append(0);
    blank.append(0);
    blank.append(0);
    blank.append(0);
    blank.append(0);
    blank.append(0);
    blank.append(0);

    Kernel kernelBlank("Select a filter", blank);
    combo->insertItem(0, kernelBlank.getName());
    kernels.insert(0, kernelBlank);

    QVector<qreal> gaussiano;
    gaussiano.append(0.0625);
    gaussiano.append(0.125);
    gaussiano.append(0.0625);
    gaussiano.append(0.125);
    gaussiano.append(0.25);
    gaussiano.append(0.125);
    gaussiano.append(0.0625);
    gaussiano.append(0.125);
    gaussiano.append(0.0625);

    Kernel kernelGaussiano("Gaussiano", gaussiano);
    combo->insertItem(1, kernelGaussiano.getName());
    kernels.insert(1, kernelGaussiano);

    QVector<qreal> laplaciano;
    laplaciano.append(0);
    laplaciano.append(-1);
    laplaciano.append(0);
    laplaciano.append(-1);
    laplaciano.append(4);
    laplaciano.append(-1);
    laplaciano.append(0);
    laplaciano.append(-1);
    laplaciano.append(0);

    Kernel kernelLaplaciano("Laplaciano", laplaciano);
    combo->insertItem(2, kernelLaplaciano.getName());
    kernels.insert(2, kernelLaplaciano);

    QVector<qreal> highPass;
    highPass.append(-1);
    highPass.append(-1);
    highPass.append(-1);
    highPass.append(-1);
    highPass.append(8);
    highPass.append(-1);
    highPass.append(-1);
    highPass.append(-1);
    highPass.append(-1);

    Kernel kernelHighPass("Generic high pass", highPass);
    combo->insertItem(3, kernelHighPass.getName());
    kernels.insert(3, kernelHighPass);

    QVector<qreal> prewittHx;
    prewittHx.append(-1);
    prewittHx.append(0);
    prewittHx.append(1);
    prewittHx.append(-1);
    prewittHx.append(0);
    prewittHx.append(1);
    prewittHx.append(-1);
    prewittHx.append(0);
    prewittHx.append(1);

    Kernel kernelPrewittHx("Prewitt Hx", prewittHx);
    combo->insertItem(4, kernelPrewittHx.getName());
    kernels.insert(4, kernelPrewittHx);

    QVector<qreal> prewittHyHx;
    prewittHyHx.append(-1);
    prewittHyHx.append(-1);
    prewittHyHx.append(-1);
    prewittHyHx.append(0);
    prewittHyHx.append(0);
    prewittHyHx.append(0);
    prewittHyHx.append(1);
    prewittHyHx.append(1);
    prewittHyHx.append(1);

    Kernel kernelPrewittHyHx("Prewitt Hy Hx", prewittHyHx);
    combo->insertItem(5, kernelPrewittHyHx.getName());
    kernels.insert(5, kernelPrewittHyHx);

    QVector<qreal> sobelHx;
    sobelHx.append(-1);
    sobelHx.append(0);
    sobelHx.append(1);
    sobelHx.append(-2);
    sobelHx.append(0);
    sobelHx.append(2);
    sobelHx.append(-1);
    sobelHx.append(0);
    sobelHx.append(1);

    Kernel kernelSobelHx("Sobel Hx", sobelHx);
    combo->insertItem(6, kernelSobelHx.getName());
    kernels.insert(6, kernelSobelHx);

    QVector<qreal> sobelHy;
    sobelHy.append(-1);
    sobelHy.append(-2);
    sobelHy.append(-1);
    sobelHy.append(0);
    sobelHy.append(0);
    sobelHy.append(0);
    sobelHy.append(1);
    sobelHy.append(2);
    sobelHy.append(1);

    Kernel kernelSobelHy("Sobel Hy", sobelHy);
    combo->insertItem(7, kernelSobelHy.getName());
    kernels.insert(7, kernelSobelHy);
}

//----------------------------------------------------
// Slots
//----------------------------------------------------
void ConvolutionWidget::comboChanged(int index)
{
    if (kernels.size() == 0)
        return;

    Kernel ker = kernels.at(index);
    QVector<qreal> k = ker.getValues();
    k11SpinBox->setValue(k.at(0));
    k12SpinBox->setValue(k.at(1));
    k13SpinBox->setValue(k.at(2));
    k21SpinBox->setValue(k.at(3));
    k22SpinBox->setValue(k.at(4));
    k23SpinBox->setValue(k.at(5));
    k31SpinBox->setValue(k.at(6));
    k32SpinBox->setValue(k.at(7));
    k33SpinBox->setValue(k.at(8));
}

void ConvolutionWidget::buttonClicked()
{
    Kernel ker = kernels.at(combo->currentIndex());
    QVector<qreal> k = ker.getValues();
    emit this->convolutionTriggered(k);
}
