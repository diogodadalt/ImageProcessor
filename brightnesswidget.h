#ifndef BRIGHTNESSWIDGET_H
#define BRIGHTNESSWIDGET_H

#include <QScrollArea>
#include <QSlider>
#include <QLineEdit>
#include <QHBoxLayout>

class BrightnessWidget : public QScrollArea
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
    explicit BrightnessWidget(QWidget *parent = 0);
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

#endif // BRIGHTNESSWIDGET_H
