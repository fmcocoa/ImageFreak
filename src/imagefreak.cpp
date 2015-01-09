#include "composite.h"
#include "imagefreak.h"

int composite_fighter(const char *fighter_name) {
    return compositeFighter(fighter_name);
}

int composite_score(const wchar_t *player1,
                    const char *player1_avatar,
                    int score1,
                    const wchar_t *player2,
                    const char *player2_avatar,
                    int score2,
                    const char *output,
                    bool isUnicode) {
    return compositeScore(player1, player1_avatar, score1, player2, player2_avatar, score2, output, isUnicode);
}
