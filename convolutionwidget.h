#ifndef CONVOLUTION_H
#define CONVOLUTION_H

#include <QScrollArea>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "kernel.h"

class ConvolutionWidget : public QScrollArea
{
    Q_OBJECT

//----------------------------------------------------
// signals
//----------------------------------------------------
signals:
    void convolutionTriggered(QVector<qreal>);

//----------------------------------------------------
// methods
//----------------------------------------------------
public:
    explicit ConvolutionWidget(QWidget *parent = 0);
    void initState();

private:
    void initComponents();
    void initKernels();
    void changeKernelValues();
//----------------------------------------------------
// slots
//----------------------------------------------------
public slots:
    void comboChanged(int index);
    void buttonClicked();

//----------------------------------------------------
// members
//----------------------------------------------------
private:
    QComboBox* combo;
    QDoubleSpinBox* k11SpinBox, *k12SpinBox, *k13SpinBox, *k21SpinBox, *k22SpinBox, *k23SpinBox, *k31SpinBox, *k32SpinBox, *k33SpinBox;
    QHBoxLayout* layoutLine1, *layoutLine2, *layoutLine3;
    QVBoxLayout* layout;
    QPushButton* button;
    QVector<Kernel> kernels;
};

#endif // CONVOLUTION_H
