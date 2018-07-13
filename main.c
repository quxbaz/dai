#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>

int init_sdl ();
SDL_Window* create_window ();
SDL_Renderer* create_renderer ();
int init_game ();
void run_game_loop (SDL_Renderer* renderer);
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
  SDL_Window* window = SDL_CreateWindow("dai", 0, 0, w, h, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("%s", SDL_GetError());
    return NULL;
  }
  return window;
}

SDL_Renderer* create_renderer (SDL_Window* window) {
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (window == NULL) {
    printf("%s", SDL_GetError());
    return NULL;
  }
  return renderer;
}

int init_game () {
  return 0;
}


void run_game_loop (SDL_Renderer* renderer) {
  bool should_run_game = true;
  SDL_Event event;

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
    // Render view
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

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

  // Constants
  const int WINDOW_WIDTH = 640;
  const int WINDOW_HEIGHT = 480;

  // Variable declarations
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  init_sdl();

  window = create_window(WINDOW_WIDTH, WINDOW_HEIGHT);
  if (window == NULL) { return 1; }

  renderer = create_renderer(window);
  if (renderer == NULL) { return 1; }

  init_game();
  run_game_loop(renderer);

  quit_sdl(window);
  return 0;
}
