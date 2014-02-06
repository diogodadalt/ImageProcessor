#include "kernel.h"

//----------------------------------------------------
// Public methods
//----------------------------------------------------
Kernel::Kernel(QObject *parent)
{
}

Kernel::Kernel(QString nam, QVector<qreal> values, QObject *parent) :
    QObject(parent), name(nam), items(values)
{
}

Kernel::Kernel(const Kernel& k)
{
    name = k.name;
    items = k.items;
}

Kernel& Kernel::operator =(const Kernel& k)
{
    name = k.name;
    items = k.items;
    return *this;
}

QString Kernel::getName()
{
    return name;
}

QVector<qreal> Kernel::getValues()
{
    return items;
}

//----------------------------------------------------
// Private methods
//----------------------------------------------------
