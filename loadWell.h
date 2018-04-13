#ifndef LOADWELL_H
#define LOADWELL_H
#include "well.h"

class LoadWell
{
public:
    LoadWell();
    Well *loadDEV(QString path);
    Well *loadWELL(QString path);
};

#endif // LOADWELL_H
