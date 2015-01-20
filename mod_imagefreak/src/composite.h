#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <cwchar>
#include "imagefreak.h"

void compositeFighter(const char *fighterName, CALLBACK_FUNC cb);

void compositeScore(const PlayerData *player1,
                    const PlayerData *player2,
                    const char *output,
                    const char *lang,
                    bool isUnicode,
                    CALLBACK_FUNC cb);

#endif
