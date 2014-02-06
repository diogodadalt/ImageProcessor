#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QVector>

class Kernel : public QObject
{
    Q_OBJECT

//----------------------------------------------------
// signals
//----------------------------------------------------
signals:

//----------------------------------------------------
// methods
//----------------------------------------------------
public:
    explicit Kernel(QObject *parent = 0);
    Kernel(QString nam, QVector<qreal> values, QObject* parent = 0);
    Kernel(const Kernel& k);

    Kernel& operator =(const Kernel& k);

    QString getName();
    QVector<qreal> getValues();

//----------------------------------------------------
// slots
//----------------------------------------------------
public slots:

//----------------------------------------------------
// members
//----------------------------------------------------
private:
    QString name;
    QVector<qreal> items;
};

#endif // KERNEL_H
