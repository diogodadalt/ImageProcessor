#include "contrastwidget.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
ContrastWidget::ContrastWidget(QWidget *parent) :
    QScrollArea(parent)
{
    initComponents();
}

void ContrastWidget::initState()
{
    textBox->setText("1");
    disconnect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    disconnect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
    slider->setValue(1);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
void ContrastWidget::initComponents()
{
    slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 255);
    slider->setValue(1);
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(updateText(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    textBox = new QLineEdit;
    textBox->setFixedSize(40, 20);
    textBox->setMaxLength(3);
    textBox->setInputMask("000");
    textBox->setText("1");
    connect(textBox, SIGNAL(returnPressed()), this, SLOT(updateSlider()));

    layout = new QHBoxLayout;
    layout->addWidget(slider);
    layout->addWidget(textBox);

    this->setLayout(layout);
}

//----------------------------------------------------
// Slots
//----------------------------------------------------
void ContrastWidget::updateText(int value)
{
    textBox->setText(QString::number(value));
}

void ContrastWidget::updateSlider()
{
    slider->setValue(textBox->text().toInt());
}
