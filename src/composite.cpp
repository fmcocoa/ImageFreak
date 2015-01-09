#include <cv.h>
#include <highgui.h>
#include <cstdio>
#include <cstring>
#include "i18nText.h"
#include "composite.h"

using namespace std;
using namespace cv;

static const char *FIGHTER_CANVAS = "../assets/fighter_canvas.png";
static const char *SCORE_CANVAS = "../assets/score_canvas.png";

static const char *UNICODE_FONT = "../assets/wqy-microhei.ttc";
static const char *ASCII_FONT = "../assets/Aero.ttf";

static const Point FIGHTER_OFFSET(-50, -160);

static const Scalar PLAYER_NAME_COLOR = CV_RGB(0x38, 0xce, 0xff);
static const Point PLAYER1_NAME_OFFSET(480, 146);
static const Point PLAYER2_NAME_OFFSET(380, 434);

static const Point PLAYER1_SCORE_CENTER(640, 156);
static const Point PLAYER2_SCORE_CENTER(540, 444);
static const int PLAYER_SCORE_WIDTH = 34;

static const Point PLAYER1_AVATAR_OFFSET(356, 120);
static const Point PLAYER2_AVATAR_OFFSET(762, 406);


void reverseStr(char *s) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

void int2str(char *s, int value) {
    for (int i = 0; value != 0; i++, value /= 10) {
        if (i == 3) {
            i = 0;
            sprintf(s, "%s,", s);
        }

        int lastDigit = value % 10;
        sprintf(s, "%s%d", s, lastDigit);
    }

    reverseStr(s);
}

void compositeImages(const Mat &background,
                     const Mat &foreground,
                     Mat &output,
                     Point2i location) {
    background.copyTo(output);


    // start at the row indicated by location, or at row 0 if location.y is negative.
    for(int y = std::max(location.y , 0); y < background.rows; ++y) {
        int fY = y - location.y; // because of the translation

        // we are done of we have processed all rows of the foreground image.
        if(fY >= foreground.rows)
          break;

        // start at the column indicated by location, 

        // or at column 0 if location.x is negative.
        for(int x = std::max(location.x, 0); x < background.cols; ++x) {
            int fX = x - location.x; // because of the translation.

            // we are done with this row if the column is outside of the foreground image.
            if(fX >= foreground.cols)
                break;

            // determine the opacity of the foregrond pixel, using its fourth (alpha) channel.
            double opacity =
                ((double)foreground.data[fY * foreground.step + fX * foreground.channels() + 3])
                / 255.;


            // and now combine the background and foreground pixel, using the opacity, 

            // but only if opacity > 0.
            for(int c = 0; opacity > 0 && c < output.channels(); ++c) {
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                    background.data[y * background.step + x * background.channels() + c];
                output.data[y*output.step + output.channels()*x + c] =
                    backgroundPx * (1.-opacity) + foregroundPx * opacity;
            }
        }
    }
}

void printScore(Mat &canvas, const char *s, int idx, Point center) {
    char numberImageName[20] = {0};
    int digitWidth, distance = 0;
    Mat numberImage;
    int offsetX[20] = {0};

    for (int i = 0; i < strlen(s); i++, distance += digitWidth) {
        offsetX[i] = distance;
        digitWidth = (s[i+1] && s[i+1] == ',') ? PLAYER_SCORE_WIDTH / 2 : PLAYER_SCORE_WIDTH;
    }

    int originX = center.x - distance / 2;
    for (int i = 0; i < strlen(s); i++) {
        sprintf(numberImageName, "../assets/numbers/%c%c.png", (s[i] == ',') ? 'x' : s[i], (idx == 1) ? 'a' : 'b');
        numberImage = imread(numberImageName, -1);
        compositeImages(canvas, numberImage, canvas, Point(originX + offsetX[i], center.y));
    }
}

bool compositeFighter(const char *fighterName) {
    Mat bg, fg, dst;

    char fighterImageName[50] = {0};
    sprintf(fighterImageName, "../fighters/%s.png", fighterName);

    // -1 to read alpha channel
    bg = imread(FIGHTER_CANVAS, -1);
    fg = imread(fighterImageName, -1);

    compositeImages(bg, fg, dst, FIGHTER_OFFSET);

    char outputPath[50] = {0};
    sprintf(outputPath, "../static/%s.png", fighterName);

    imwrite(outputPath, dst);

    return true;
}

bool compositeScore(const wchar_t *player1,
                    const char *player1_avatar,
                    int score1,
                    const wchar_t *player2,
                    const char *player2_avatar,
                    int score2,
                    const char *output,
                    bool isUnicode) {
    Mat bg, avatar1, avatar2;

    i18nText i18n;
    if (isUnicode) {
        i18n.setFont(UNICODE_FONT);
    } else {
        i18n.setFont(ASCII_FONT);
    }

    // -1 to read alpha channel
    bg = imread(SCORE_CANVAS, -1);

    // Avatars
    char a1[100] = {0};
    char a2[100] = {0};

    sprintf(a1, "avatars/%s.png", player1_avatar);
    sprintf(a2, "avatars/%s.png", player2_avatar);

    avatar1 = imread(a1, -1);
    avatar2 = imread(a2, -1);

    compositeImages(bg, avatar1, bg, PLAYER1_AVATAR_OFFSET);
    compositeImages(bg, avatar2, bg, PLAYER2_AVATAR_OFFSET);

    // Names
    i18n.putText(bg, player1, PLAYER1_NAME_OFFSET, PLAYER_NAME_COLOR);
    i18n.putText(bg, player2, PLAYER2_NAME_OFFSET, PLAYER_NAME_COLOR);

    // Scores
    char s1[20] = {0};
    char s2[20] = {0};

    int2str(s1, score1);
    int2str(s2, score2);

    printScore(bg, s1, 1, PLAYER1_SCORE_CENTER);
    printScore(bg, s2, 2, PLAYER2_SCORE_CENTER);

    char outputPath[100] = {0};
    sprintf(outputPath, "../static/%s.png", output);
    imwrite(outputPath, bg);

    return true;
}
