#ifndef IMAGE_FREAK_H
#define IMAGE_FREAK_H

#include <cwchar>

extern "C" {

int composite_fighter(const char *fighter_name);

int composite_score(const wchar_t *player1,
                      int score1,
                      const wchar_t *player2,
                      int score2,
                      bool isUnicode);

}

#endif
