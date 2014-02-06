#ifndef ZOOMWIDGET_H
#define ZOOMWIDGET_H

#include <QScrollArea>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

class ZoomWidget : public QScrollArea
{
    Q_OBJECT

//----------------------------------------------------
// signals
//----------------------------------------------------
signals:
    void zoomOut(int wVal, int hVal);
    void zoomIn();

//----------------------------------------------------
// methods
//----------------------------------------------------
public:
    explicit ZoomWidget(QWidget *parent = 0);
    void initState();

private:
    void initComponents();

//----------------------------------------------------
// slots
//----------------------------------------------------
public slots:
    void zoomOutButtonClicked();
    void zoomInButtonClicked();

//----------------------------------------------------
// members
//----------------------------------------------------
private:
    QPushButton* buttonZoomIn;
    QPushButton* buttonZoomOut;
    QLabel* labelZoomOutWidth;
    QLabel* labelZoomOutHeight;
    QSpinBox* spinBoxZoomOutWidth;
    QSpinBox* spinBoxZoomOutHeight;
    QVBoxLayout* layoutZoom;
    QHBoxLayout* layoutZoomOutWidth;
    QHBoxLayout* layoutZoomOutHeight;
};

#endif // ZOOMWIDGET_H
