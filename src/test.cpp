#include <cwchar>
#include <highgui.h>
#include "imagefreak.h"

using namespace cv;

int main() {
    //composite_fighter("1");
    composite_score(L"PLAYER NAME", 1234567, L"PLAYER NAME", 200, 0);

    waitKey(0);
    return 0;
}
