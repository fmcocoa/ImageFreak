#ifndef IMAGE_FREAK_H
#define IMAGE_FREAK_H

#include <cwchar>

#define STATUS_OK  0
#define STATUS_ERR 1

extern "C" {

typedef void (*CALLBACK_FUNC)(int status, const char *err_msg);

struct PlayerData {
    const wchar_t *name;
    const char *avatar;
    int score;
};

void composite_fighter(const char *fighter_name, CALLBACK_FUNC cb);

void composite_score(const wchar_t *player1_name,
                     const char *player1_avatar,
                     int player1_score,
                     const wchar_t *player2_name,
                     const char *player2_avatar,
                     int player2_score,
                     const char *output,         // The output image path
                     int isUnicode,              // If player's name is unicode
                     CALLBACK_FUNC cb);

}

#endif
