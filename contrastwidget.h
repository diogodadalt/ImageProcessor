#ifndef CONTRASTWIDGET_H
#define CONTRASTWIDGET_H

#include <QScrollArea>
#include <QSlider>
#include <QLineEdit>
#include <QHBoxLayout>

class ContrastWidget : public QScrollArea
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
    explicit ContrastWidget(QWidget *parent = 0);
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

#endif // CONTRASTWIDGET_H
