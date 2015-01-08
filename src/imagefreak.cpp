#include "composite.h"
#include "imagefreak.h"

int composite_fighter(const char *fighter_name) {
    return compositeFighter(fighter_name);
}

int composite_score(const wchar_t *player1,
                    int score1,
                    const wchar_t *player2,
                    int score2,
                    bool isUnicode) {
    return compositeScore(player1, score1, player2, score2, isUnicode);
}
