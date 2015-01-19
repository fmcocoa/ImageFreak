#include <cv.h>
#include <highgui.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "i18nText.h"
#include "composite.h"

using namespace std;
using namespace cv;


// Pre-defined constants //
static const char *FIGHTER_CANVAS = "assets/fighter_canvas.png";
static const char *SCORE_CANVAS = "assets/score_canvas.png";

static const char *UNICODE_FONT = "assets/wqy-microhei.ttc";
static const char *ASCII_FONT = "assets/Aero.ttf";

static const Point FIGHTER_OFFSET(-50, -160);

static const Scalar PLAYER_NAME_COLOR = CV_RGB(0x38, 0xce, 0xff);
static const Point PLAYER1_NAME_OFFSET(480, 146);
static const Point PLAYER2_NAME_OFFSET(380, 434);

static const Point PLAYER1_SCORE_CENTER(640, 156);
static const Point PLAYER2_SCORE_CENTER(546, 444);
static const int PLAYER_SCORE_WIDTH = 34;

static const Point PLAYER1_AVATAR_OFFSET(353, 117);
static const Point PLAYER2_AVATAR_OFFSET(763, 404);

//
// Reverse a c-string
//
void reverseStr(char *s) {
    for (int i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
    }
}

//
// Convert an int value to string with such format: 'x,xxx,xxx'
//
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

//
// Composite two images
//
void compositeImages(const Mat &background,
                     const Mat &foreground,
                     Point2i location) {
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
            for(int c = 0; opacity > 0 && c < background.channels(); ++c) {
                unsigned char foregroundPx =
                    foreground.data[fY * foreground.step + fX * foreground.channels() + c];
                unsigned char backgroundPx =
                    background.data[y * background.step + x * background.channels() + c];
                background.data[y*background.step + background.channels()*x + c] =
                    backgroundPx * (1.-opacity) + foregroundPx * opacity;
            }
        }
    }
}

//
// Put score data onto canvas
//
void printScore(Mat &canvas, const char *s, int idx, Point center) {
    int digitWidth, distance = 0;
    Mat numberImage;
    int offsetX[20] = {0};

    for (size_t i = 0; i < strlen(s); i++, distance += digitWidth) {
        offsetX[i] = distance;
        digitWidth = (s[i+1] && s[i+1] == ',') ? PLAYER_SCORE_WIDTH / 2 : PLAYER_SCORE_WIDTH;
    }

    int originX = center.x - distance / 2;
    for (size_t i = 0; i < strlen(s); i++) {
        char numberImageName[20] = {0};
        sprintf(numberImageName, "assets/numbers/%c%c.png", (s[i] == ',') ? 'x' : s[i], (idx == 1) ? 'a' : 'b');
        numberImage = imread(numberImageName, -1);
        compositeImages(canvas, numberImage, Point(originX + offsetX[i], center.y));
    }
}

//
// Composite a fighter
//
void compositeFighter(const char *fighterName, CALLBACK_FUNC cb) {
    Mat bg, fg;

    char fighterImageName[50] = {0};
    sprintf(fighterImageName, "fighters/%s.png", fighterName);

    try {
        // -1 to read alpha channel
        bg = imread(FIGHTER_CANVAS, -1);
        fg = imread(fighterImageName, -1);

        compositeImages(bg, fg, FIGHTER_OFFSET);

        char outputPath[50] = {0};
        sprintf(outputPath, "static/%s.jpg", fighterName);

        imwrite(outputPath, bg);

        if (cb) {
            cb(STATUS_OK, NULL);
        }
    } catch (cv::Exception &e) {
        if (cb) {
            cb(STATUS_ERR, e.what());
        }
    }
}

//
// Composite game score
//
void compositeScore(const PlayerData *player1,
                    const PlayerData *player2,
                    const char *output,
                    bool isUnicode,
                    CALLBACK_FUNC cb) {
    Mat bg, avatar1, avatar2;
    Mat mask, roi;

    try {
        // -1 to read alpha channel
        bg = imread(SCORE_CANVAS, -1);

        // Avatars
        char a1[100] = {0};
        char a2[100] = {0};

        sprintf(a1, "avatars/%s", player1->avatar);
        sprintf(a2, "avatars/%s", player2->avatar);

        avatar1 = imread(a1);
        mask = imread(a1, 0);
        roi = bg(Rect(PLAYER1_AVATAR_OFFSET.x, PLAYER1_AVATAR_OFFSET.y, mask.cols, mask.rows));
        avatar1.copyTo(roi, mask);

        avatar2 = imread(a2);
        mask = imread(a2, 0);
        roi = bg(Rect(PLAYER2_AVATAR_OFFSET.x, PLAYER2_AVATAR_OFFSET.y, mask.cols, mask.rows));
        avatar2.copyTo(roi, mask);

        //compositeImages(bg, avatar1, PLAYER1_AVATAR_OFFSET);
        //compositeImages(bg, avatar2, PLAYER2_AVATAR_OFFSET);

        i18nText i18n;
        if (isUnicode) {
            i18n.setFont(UNICODE_FONT);
        } else {
            i18n.setFont(ASCII_FONT);
        }

        // Names
        i18n.putText(bg, player1->name, PLAYER1_NAME_OFFSET, PLAYER_NAME_COLOR);
        i18n.putText(bg, player2->name, PLAYER2_NAME_OFFSET, PLAYER_NAME_COLOR);

        // Scores
        char score1[20] = {0};
        char score2[20] = {0};

        int2str(score1, player1->score);
        int2str(score2, player2->score);

        printScore(bg, score1, 1, PLAYER1_SCORE_CENTER);
        printScore(bg, score2, 2, PLAYER2_SCORE_CENTER);

        char outputPath[100] = {0};
        sprintf(outputPath, "static/%s", output);
        imwrite(outputPath, bg);

        if (cb) {
            cb(STATUS_OK, NULL);
        }
    } catch (cv::Exception &e) {
        if (cb) {
            cb(STATUS_ERR, e.what());
        }
    }
}
