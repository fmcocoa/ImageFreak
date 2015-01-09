#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <cwchar>

bool compositeFighter(const char *fighterName);
bool compositeScore(const wchar_t *player1,
                    const char *player1_avatar,
                    int score1,
                    const wchar_t *player2,
                    const char *player2_avatar,
                    int score2,
                    const char *output,
                    bool isUnicode);

#endif
