#include "composite.h"
#include "imagefreak.h"

void composite_fighter(const char *fighter_name, CALLBACK_FUNC cb) {
    compositeFighter(fighter_name, cb);
}

void composite_score(const wchar_t *player1_name,
                     const char *player1_avatar,
                     int player1_score,
                     const wchar_t *player2_name,
                     const char *player2_avatar,
                     int player2_score,
                     const char *output,         // The output image path
                     int isUnicode,              // If player's name is unicode
                     CALLBACK_FUNC cb) {
    PlayerData player1 = {player1_name, player1_avatar, player1_score};
    PlayerData player2 = {player2_name, player2_avatar, player2_score};
    compositeScore(&player1, &player2, output, (bool)isUnicode, cb);
}
