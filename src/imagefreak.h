#ifndef IMAGE_FREAK_H
#define IMAGE_FREAK_H

#include <cwchar>

//struct PlayerData {
    //const wchar_t *name;
    //const char *avatar;
    //int score;
//};

extern "C" {

int composite_fighter(const char *fighter_name);

int composite_score(const wchar_t *player1,
                    const char *player1_avatar,
                    int score1,
                    const wchar_t *player2,
                    const char *player2_avatar,
                    int score2,
                    const char *output,
                    bool isUnicode);

}

#endif
