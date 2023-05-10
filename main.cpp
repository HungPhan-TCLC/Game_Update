
#include <iostream>
#include <SDL2/SDL.h>
#include "SDL_mixer.h"
#include "SDL_utils.h"
#include "display.h"
#include "player3.h"
#include "2Player16.h"

using namespace std;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *bg1;
SDL_Texture *volume;
bool sound;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;
SDL_Rect src = {0, 0, 306, 244};
SDL_Rect dest ={350, 280, 100, 80};
const string WINDOW_TITLE = "Game CARO code by Hùng Phan";

void Render(){
    SDL_RenderClear(renderer);
    renderTexture(bg1, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    renderTexture2(volume, renderer, src, dest, sound);
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[])
{
    initSDL(window, renderer,SCREEN_WIDTH,  SCREEN_HEIGHT, WINDOW_TITLE);

    //draw_Bg(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //SDL_RenderPresent(renderer);
    //draw_board(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //playOneGame1Player(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //playOneGame2Player(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    //playOneGame2Player16(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("%s", Mix_GetError());
    }

    Mix_Chunk* click1 = NULL;
    Mix_Chunk* click2 = NULL;
    Mix_Music* music = NULL;

    //Load Sound Effect
    click1 = Mix_LoadWAV("click1.wav");
    click2 = Mix_LoadWAV("click2.wav");
    music = Mix_LoadMUS("Beat_chill.mp3");

    Mix_PlayMusic(music, -1);

homee:
    //Màn hình ban đầu
    sound = true;
    bg1 = loadTexture("Game/File_image/bg1.png", renderer);
    volume = loadTexture("Game/File_image/volume.png",renderer);

    int choice= -1;
    SDL_Event e;
    SDL_Rect filled_rect;
    while (true) {
        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            filled_rect.x = e.button.x; // Lấy hoành độ x của chuột
            filled_rect.y = e.button.y; // Lấy tung độ y của chuột
            if (filled_rect.x >= 145 && filled_rect.y >= 315 && filled_rect.x <= 310 && filled_rect.y <= 390){
                    choice = 1;
                    break;
            }
            if (filled_rect.x >= 475 && filled_rect.y >= 325 && filled_rect.x <= 645 && filled_rect.y <= 390){
                    choice = 2;
                    break;
            }
            if(filled_rect.x >= 360 && filled_rect.y >= 280 && filled_rect.x <= 360+100 && filled_rect.y <= 280+80){
                if(sound){
                    src.x = 306;
                    sound = false;
                    Mix_HaltMusic();
                    renderTexture2(volume, renderer, src, dest, sound);
                }
                else{
                    src.x = 0;
                    sound = true;
                    Mix_PlayMusic(music, -1);
                    renderTexture2(volume, renderer, src, dest, sound);
                }
            }
        }
        Render();
    }
    cout << choice;
    //1Player
    if (choice == 1)
    {   Mix_PlayChannel (-1, click2, 0);
        return_game:
        playOneGame1Player(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        endGame(renderer);
        if (returnn(renderer) == 2){
            Mix_PlayChannel (-1, click2, 0);
            goto return_game;
        }
        else
        {
            Mix_PlayChannel (-1, click2, 0);
            goto homee;
        }

    }
    //2 Player
    if (choice == 2) {
            //Man hinh lua chon map
            Mix_PlayChannel (-1, click2, 0);
            SDL_RenderClear(renderer);
            SDL_Texture *bg2Player = loadTexture("Game/File_image/bg2Player.png", renderer);
            renderTexture(bg2Player, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderPresent(renderer);
            int choice2;
            while (true) {
            SDL_Delay(10);
            if ( SDL_WaitEvent(&e) == 0) continue;
            if (e.type == SDL_QUIT) break;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                filled_rect.x = e.button.x; // Lấy hoành độ x của chuột
                filled_rect.y = e.button.y; // Lấy tung độ y của chuột
                if (filled_rect.x >= 100 && filled_rect.y >= 230 && filled_rect.x <= 310 && filled_rect.y <= 300){
                        choice2 = 1;
                        break;
                }
                if (filled_rect.x >= 465 && filled_rect.y >= 230 && filled_rect.x <= 685 && filled_rect.y <= 300){
                        choice2 = 2;
                        break;
                }
            }
        }

        cout << endl << choice2;
        //2player -> 3x3
        if (choice2 == 1)
        {
            Mix_PlayChannel (-1, click2, 0);
            return_game21:
            playOneGame2Player(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            endGame(renderer);
            if (returnn(renderer) == 2)
            {
                Mix_PlayChannel (-1, click2, 0);
                goto return_game21;
            }
            else
            {
                Mix_PlayChannel (-1, click2, 0);
                goto homee;
            }
        }
        //2player -> 16x16
        if (choice2 == 2)
        {
            Mix_PlayChannel (-1, click2, 0);
            return_game22:
            playOneGame2Player16(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            endGame(renderer);
            if (returnn(renderer) == 2)
            {
                Mix_PlayChannel (-1, click2, 0);
                goto return_game22;
            }
            else
            {   
                if(returnn(renderer) == 1)
                {
                    Mix_PlayChannel (-1, click2, 0);
                    goto homee;
                } 
            }
        }
    }

    if(choice==-1)
    {
       
        quitSDL(window, renderer);
    }
    return 0;
}