#ifndef LOADSTRATASURFACE_H
#define LOADSTRATASURFACE_H

#include "strataSurface.h"
class LoadStrataSurface
{
public:
    LoadStrataSurface();
    StrataSurface* loadTin(QString);
    StrataSurface* loadSS(QString);

};

#endif // LOADSTRATASURFACE_H
