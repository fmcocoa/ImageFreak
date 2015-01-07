#include <iostream>
#include <string.h>
#include <list>
#include <Magick++.h>
#include "freak.h"

using namespace std;
using namespace Magick;

void initMagick(const char *workpath) {
    InitializeMagick(workpath);
}

bool _compositeImages(const list<string> &imagePaths,
                     const list<t_offset> &offsets,
                     const string &outputPath) {
    try {
        list<string>::const_iterator pathPos = imagePaths.begin();
        list<t_offset>::const_iterator offsetPos = offsets.begin();

        Image image(*pathPos);

        ++pathPos;
        ++offsetPos;

        for (; pathPos != imagePaths.end(); ++pathPos) {
            cout << *pathPos << " " << (*offsetPos).x << " " << (*offsetPos).y << endl;
            image.composite(Image(*pathPos), (*offsetPos).x, (*offsetPos).y);
        }

        image.write(outputPath);
        return true;
    } catch (Magick::Exception &error_) {
        return false;
    }
}

int compositeImages(const char *workpath,
                    const char *imageSpecs[],
                    const t_offset *offsets_,
                    int n,
                    const char *outputSpec) {
    initMagick(workpath);

    list<string> paths;
    list<t_offset> offsets;
    string outputPath(outputSpec);

    for (int i = 0; i < n; i++) {
        paths.push_back(imageSpecs[i]);
        offsets.push_back(offsets_[i]);
    }

    return _compositeImages(paths, offsets, outputPath);
}
