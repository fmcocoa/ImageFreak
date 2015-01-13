CC = g++
CFLAGS = -o2 -ansi -Wall -Wextra -Wno-overloaded-virtual -Isrc
LDFLAGS =

SOURCES = \
	src/composite.cpp \
	src/i18nText.cpp \
	src/imagefreak.cpp

CFLAGS += `pkg-config --cflags --libs opencv`
CFLAGS += -L/usr/local/Cellar/freetype/2.5.5/lib
CFLAGS += -I/usr/local/Cellar/freetype/2.5.5/include/freetype2
CFLAGS += -lfreetype

all: libimagefreak.so

libimagefreak.so: $(SOURCES)
	$(CC) -shared -fPIC $^ $(CFLAGS) -o $@

clean:
	$(RM) src/*.o
	$(RM) libimagefreak.so

test: $(SOURCES) src/test.cpp
	$(CC) $^ $(CFLAGS) -o test_imagefreak -g
