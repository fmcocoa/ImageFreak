#include <iostream>
#include "freak.h"

using namespace std;

int main(int argc, char **argv) {
    const char *imageSpec[] = {"1.jpg", "2.jpg"};
    t_offset offset_1 = {0, 0};
    t_offset offset_2 = {100, 100};
    t_offset offsets[] = {offset_1, offset_2};

    compositeImages(argv[0], imageSpec, offsets, 2, "out.jpg");
}
