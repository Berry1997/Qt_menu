#include "data.h"
#include <iostream>


Data::Data(QObject *parent) : QObject(parent)
{
    std::cout<<"constructed"<<std::endl;
    menu.append({QStringLiteral("A"),QStringLiteral("1"),QStringLiteral("null"),QVariantList()});
}

