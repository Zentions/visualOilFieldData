#ifndef LOADEXPLORATIONRESULT_H
#define LOADEXPLORATIONRESULT_H

#include "explorationResult.h"
class LoadExplorationResult
{
public:
    LoadExplorationResult();
    ExplorationResult * loadPicAndText(QString);
    ExplorationResult* loadExp(QString);
    ExplorationResult* loadByteExp(QString);
};

#endif // LOADEXPLORATIONRESULT_H
