#include "zoomwidget.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
ZoomWidget::ZoomWidget(QWidget *parent) :
    QScrollArea(parent)
{
    initComponents();
}

void ZoomWidget::initState()
{
    spinBoxZoomOutWidth->setValue(1);
    spinBoxZoomOutHeight->setValue(1);
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
void ZoomWidget::initComponents()
{
    buttonZoomIn = new QPushButton("Zoom in 2x2");
    connect(buttonZoomIn, SIGNAL(clicked()), this, SLOT(zoomInButtonClicked()));

    labelZoomOutWidth = new QLabel("Width factor");
    spinBoxZoomOutWidth = new QSpinBox;
    spinBoxZoomOutWidth->setRange(1, 10);
    layoutZoomOutWidth = new QHBoxLayout;
    layoutZoomOutWidth->addWidget(labelZoomOutWidth);
    layoutZoomOutWidth->addWidget(spinBoxZoomOutWidth);

    labelZoomOutHeight = new QLabel("Height factor");
    spinBoxZoomOutHeight = new QSpinBox;
    spinBoxZoomOutHeight->setRange(1, 10);
    layoutZoomOutHeight = new QHBoxLayout;
    layoutZoomOutHeight->addWidget(labelZoomOutHeight);
    layoutZoomOutHeight->addWidget(spinBoxZoomOutHeight);

    buttonZoomOut = new QPushButton("Zoom out");
    connect(buttonZoomOut, SIGNAL(clicked()), this, SLOT(zoomOutButtonClicked()));

    layoutZoom = new QVBoxLayout;
    layoutZoom->addWidget(buttonZoomIn);
    layoutZoom->addLayout(layoutZoomOutWidth);
    layoutZoom->addLayout(layoutZoomOutHeight);
    layoutZoom->addWidget(buttonZoomOut);
    this->setLayout(layoutZoom);
}

//----------------------------------------------------
// Slots
//----------------------------------------------------
void ZoomWidget::zoomOutButtonClicked()
{
    emit this->zoomOut(spinBoxZoomOutWidth->value(), spinBoxZoomOutHeight->value());
}

void ZoomWidget::zoomInButtonClicked()
{
    emit this->zoomIn();
}
