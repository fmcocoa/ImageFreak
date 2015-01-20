CC = g++
CFLAGS = -o2 -ansi -Wall -Wextra -Wno-overloaded-virtual -Isrc

CFLAGS += `pkg-config --cflags --libs opencv`
CFLAGS += `freetype-config --cflags`
CFLAGS += `freetype-config --libs`

SOURCES = \
	src/composite.cpp \
	src/i18nText.cpp \
	src/imagefreak.cpp

all: libimagefreak.so

libimagefreak.so: $(SOURCES)
	$(CC) -shared -fPIC $^ $(CFLAGS) -o ../$@

clean:
	$(RM) src/*.o
	$(RM) libimagefreak.so

test: $(SOURCES) src/test.cpp
	$(CC) $^ $(CFLAGS) -o ../test_imagefreak -g
