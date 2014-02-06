#ifndef QUANTIZATIONWIDGET_H
#define QUANTIZATIONWIDGET_H

#include <QScrollArea>
#include <QSlider>
#include <QLineEdit>
#include <QHBoxLayout>

class QuantizationWidget : public QScrollArea
{
    Q_OBJECT

//----------------------------------------------------
// signals
//----------------------------------------------------
signals:
    void valueChanged(int);

//----------------------------------------------------
// methods
//----------------------------------------------------
public:
    explicit QuantizationWidget(QWidget *parent = 0);
    void initState();

private:
    void initComponents();

//----------------------------------------------------
// slots
//----------------------------------------------------
public slots:
    void updateText(int value);
    void updateSlider();

//----------------------------------------------------
// members
//----------------------------------------------------
private:
    QSlider* slider;
    QLineEdit* textBox;
    QHBoxLayout* layout;
};

#endif // QUANTIZATIONWIDGET_H
