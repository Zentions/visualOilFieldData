#ifndef LOADPROFILE_H
#define LOADPROFILE_H

#include "profile.h"
class LoadProfile
{
public:
    LoadProfile();
    Profile * loadPicAndText(QString);
    Profile* loadPro(QString);
    //加载不含图片像素坐标的文件
    Profile* loadProCal(QString);
};

#endif // LOADPROFILE_H
