/*
pattern - show pattern like in the old xorg days
Written in 2007 by <Ahmet Inan> <xdsopl@googlemail.com>
To the extent possible under law, the author(s) have dedicated all copyright and related and neighboring rights to this software to the public domain worldwide. This software is distributed without any warranty.
You should have received a copy of the CC0 Public Domain Dedication along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

#include <SDL.h>

void draw(SDL_Surface *surface)
{
	Uint32 *fbp = (Uint32 *)(surface->pixels);
	switch (surface->format->BytesPerPixel) {
		case 1:
			for (int h = 0; h < surface->h >> 2; h++) {
				for (int w = 0; w < surface->w >> 2; w++)
					*fbp++ = 0x000000ff;
				for (int w = 0; w < surface->w >> 2; w++)
					*fbp++ = 0x00ff0000;
				for (int w = 0; w < surface->w >> 2; w++)
					*fbp++ = 0x0000ff00;
				for (int w = 0; w < surface->w >> 2; w++)
					*fbp++ = 0xff000000;
			}
			break;
		case 2:
			for (int h = 0; h < surface->h >> 2; h++) {
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x00000000;
					*fbp++ = 0x0000ffff;
				}
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x0000ffff;
					*fbp++ = 0x00000000;
				}
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x00000000;
					*fbp++ = 0xffff0000;
				}
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0xffff0000;
					*fbp++ = 0x00000000;
				}
			}
			break;
		case 4:
			for (int h = 0; h < surface->h >> 2; h++) {
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x00000000;
					*fbp++ = 0x00000000;
					*fbp++ = 0x00000000;
					*fbp++ = 0x00ffffff;
				}
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x00000000;
					*fbp++ = 0x00ffffff;
					*fbp++ = 0x00000000;
					*fbp++ = 0x00000000;
				}
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x00000000;
					*fbp++ = 0x00000000;
					*fbp++ = 0x00ffffff;
					*fbp++ = 0x00000000;
				}
				for (int w = 0; w < surface->w >> 2; w++) {
					*fbp++ = 0x00ffffff;
					*fbp++ = 0x00000000;
					*fbp++ = 0x00000000;
					*fbp++ = 0x00000000;
				}
			}
			break;
		default:
			/* awwwwww, tough luck. */
			break;
	}
	SDL_Flip(surface);
}

void handle_events()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
				exit(0);
				break;
			case SDL_QUIT:
				exit(0);
				break;
			default:
				break;
		}
	}

}

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	const SDL_VideoInfo *const info = SDL_GetVideoInfo();
	SDL_Surface *surface = SDL_SetVideoMode(info->current_w, info->current_h, 0,
		SDL_SWSURFACE|SDL_NOFRAME);
	if (!surface)
		return 1;
	fprintf(stderr, "w=%d, h=%d\n", surface->w, surface->h);
	SDL_WM_SetCaption("Hmmmm, Pattern", "pattern");
	SDL_ShowCursor(0);
	draw(surface);
	for (;;) {
		SDL_Delay(100);
		handle_events();
	}
	return 0;
}

