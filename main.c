#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int init_sdl ();
SDL_Window* create_window ();
int init_game ();
void run_game_loop ();
void read_input ();
void handle_input ();
void quit_sdl ();

int init_sdl () {
  /*
    Returns 0 for success, else returns error code > 0.
  */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("%s", SDL_GetError());
    return 1;
  }
  return 0;
}

SDL_Window* create_window (int w, int h) {
  /*
    Returns 0 for success, else returns error code > 0.
  */
  SDL_Window* window = SDL_CreateWindow("working title", 0, 0, w, h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("%s", SDL_GetError());
    return NULL;
  }
  return window;
}

int init_game () {
  return 0;
}


void run_game_loop () {
  bool should_run_game = true;
  SDL_Event event;

  // Render background
  /* SDL_ */

  while (should_run_game) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        should_run_game = false;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
        case SDLK_q:
          should_run_game = false;
          break;
        }
      }
    }
    SDL_Delay(16);
  }
}

void read_input () {}

void handle_input () {}

void quit_sdl (SDL_Window* window) {
  SDL_DestroyWindow(window);
  /* IMG_Quit(); */
  SDL_Quit();
};

int main (int argc, char* args[]) {
  /*
    Return 0 for success, else return error code > 0.
  */

  // Variable declarations
  SDL_Window* window = NULL;
  const int WINDOW_WIDTH = 640;
  const int WINDOW_HEIGHT = 480;

  init_sdl();

  window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT);
  if (window == NULL) { return 1; }

  init_game();
  run_game_loop();

  quit_sdl(window);
  return 0;
}
