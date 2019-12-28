
INCLUDES ?= -Isrc/ -Iimg/
PKG_CONFIG ?= pkg-config
SDL_LDFLAGS ?= `$(PKG_CONFIG) --libs sdl2`
SDL_CFLAGS ?= `$(PKG_CONFIG) --cflags sdl2`
F_LDFLAGS += $(SDL_LDFLAGS)
F_CFLAGS += -O2 -Wall -pedantic -std=gnu11
F_CFLAGS += $(SDL_CFLAGS)

all: images
	$(CC) src/*.c $(CFLAGS) $(F_CFLAGS) $(INCLUDES) -o main $(LDFLAGS) $(F_LDFLAGS)

images: tools
	./concoord/concoord img/*.yaml

tools:
	make -C concoord

memtest:
	valgrind --track-origins=yes --leak-check=yes ./main

opk:
	mksquashfs main assets/* facegame.opk -all-root -noappend -no-exports -no-xattrs -no-progress
