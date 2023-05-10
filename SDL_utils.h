
#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_image.h"

using namespace std;

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string &WINDOW_TITLE);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
void renderTexture2(SDL_Texture *tex, SDL_Renderer *ren, SDL_Rect src, SDL_Rect dest, bool click);


#endif // SDL_UTILS