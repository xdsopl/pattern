
CFLAGS = -std=c99 -Wall -W -O3 $(shell sdl-config --cflags)
LDFLAGS = $(shell sdl-config --libs)

pattern: pattern.c

clean:
	rm -f pattern

