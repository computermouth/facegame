
INCLUDES ?= -Isrc/ -Iimg/
PKG_CONFIG ?= pkg-config
SDL_LDFLAGS ?= `$(PKG_CONFIG) --libs sdl2`
SDL_CFLAGS ?= `$(PKG_CONFIG) --cflags sdl2`
F_LDFLAGS += $(SDL_LDFLAGS)
F_CFLAGS += -O2 -Wall -pedantic -std=gnu11
F_CFLAGS += $(SDL_CFLAGS)

GAM_SRC = $(wildcard src/*.c)
GAM_OBJ = $(GAM_SRC:.c=.o)

IMG_YML = $(wildcard img/*.yaml)
IMG_SRC = $(IMG_YML:.yaml=.c)
IMG_OBJ = $(IMG_SRC:.c=.o)

all: tools $(IMG_SRC) $(GAM_OBJ) $(IMG_OBJ)
	$(CC) -o main $(GAM_OBJ) $(IMG_OBJ) $(LDFLAGS) $(F_LDFLAGS)

%.c: %.yaml
	./concoord/concoord $<

%.o: %.c
	$(CC) $(CFLAGS) $(F_CFLAGS) $(INCLUDES) -c $< -o $@

tools:
	make -C concoord

memtest:
	valgrind --track-origins=yes --leak-check=yes ./main

opk:
	mksquashfs main assets/* facegame.opk -all-root -noappend -no-exports -no-xattrs -no-progress
