#ifndef FREAK_H
#define FREAK_H

typedef struct {
    long x;
    long y;
} t_offset;

extern "C" {

int compositeImages(const char *workpath,
                    const char *imageSpecs[],
                    const t_offset *offsets_,
                    int n,
                    const char *outputSpec);

}

#endif
