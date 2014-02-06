#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>
#include <QImage>
#include <QPoint>
#include <qmath.h>

struct InValues
{
    QPoint pos;
    uint color;
    int val;
};

struct OutValues
{
    QPoint pos;
    uint color;
};

class Operation : public QObject
{
    Q_OBJECT

//----------------------------------------------------
// signals
//----------------------------------------------------

//----------------------------------------------------
// methods
//----------------------------------------------------
public:
    explicit Operation(QObject *parent = 0);
    static QImage flipHorizontal(QImage in);
    static QImage flipVertical(QImage in);
    static QImage luminance(QImage in);
    static QImage negative(QImage in);
    static QImage quantization(QImage in, int value);
    static QImage brightness(QImage in, int value);
    static QImage contrast(QImage in, int value);
    static QImage histogram(QImage in);
    static QImage histogramEqualization(QImage in);
    static QImage zoomOut(QImage img, int wVal, int hVal);
    static QImage zoomIn(QImage img); //2x
    static QImage rotateLeft(QImage img);
    static QImage rotateRight(QImage img);
    static QImage convolution(QImage img, QVector<qreal> kernel);

private:
    static QImage punctualOperation(QImage in, int value, OutValues (*oper)(QImage in, InValues inVals));
    static OutValues flipHor(QImage in, InValues inVals);
    static OutValues flipVer(QImage in, InValues inVals);
    static OutValues lum(QImage in, InValues inVals);
    static OutValues neg(QImage in, InValues inVals);
    static OutValues quant(QImage in, InValues inVals);
    static OutValues bright(QImage in, InValues inVals);
    static OutValues contr(QImage in, InValues inVals);


signals:

//----------------------------------------------------
// slots
//----------------------------------------------------
public slots:


//----------------------------------------------------
// members
//----------------------------------------------------

};

#endif // OPERATION_H
