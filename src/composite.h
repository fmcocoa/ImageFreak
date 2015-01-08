#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <cwchar>

bool compositeFighter(const char *fighterName);
bool compositeScore(const wchar_t *player1,
                      int score1,
                      const wchar_t *player2,
                      int score2,
                      bool isUnicode);

#endif
