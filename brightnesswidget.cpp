#include "brightnesswidget.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
BrightnessWidget::BrightnessWidget(QWidget *parent) :
    QScrollArea(parent)
{
    initComponents();
}

void BrightnessWidget::initState()
{
    textBox->setText("0");
    disconnect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    disconnect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
    slider->setValue(0);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
void BrightnessWidget::initComponents()
{
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(-255, 255);
    slider->setValue(0);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    textBox = new QLineEdit;
    textBox->setFixedSize(40, 20);
    textBox->setMaxLength(3);
    textBox->setInputMask("000"); //-?\\d{1,3}
    textBox->setText("0");
    connect(textBox, SIGNAL(returnPressed()), this, SLOT(updateSlider()));

    layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(textBox);

    this->setLayout(layout);
}

//----------------------------------------------------
// Slots
//----------------------------------------------------
void BrightnessWidget::updateText(int value)
{
    textBox->setText(QString::number(value));
}

void BrightnessWidget::updateSlider()
{
    slider->setValue(textBox->text().toInt());
}
