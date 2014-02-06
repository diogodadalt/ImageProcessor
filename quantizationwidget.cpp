#include "quantizationwidget.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
QuantizationWidget::QuantizationWidget(QWidget *parent) :
    QScrollArea(parent)
{
    initComponents();
}

void QuantizationWidget::initState()
{
    textBox->setText("256");
    disconnect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    disconnect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
    slider->setValue(255);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
void QuantizationWidget::initComponents()
{
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 256);
    slider->setValue(256);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    textBox = new QLineEdit;
    textBox->setFixedSize(40, 20);
    textBox->setMaxLength(3);
    textBox->setInputMask("000");
    textBox->setText("256");
    connect(textBox, SIGNAL(returnPressed()), this, SLOT(updateSlider()));

    layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(textBox);

    this->setLayout(layout);
}

//----------------------------------------------------
// Slots
//----------------------------------------------------
void QuantizationWidget::updateText(int value)
{
    textBox->setText(QString::number(value));
}

void QuantizationWidget::updateSlider()
{
    slider->setValue(textBox->text().toInt());
}
