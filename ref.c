#include <stdbool.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define N_FRAMES 4

int current_frame = 0;
SDL_Rect sprite_rects[N_FRAMES];

SDL_Texture* person_texture = NULL;

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* square = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* colors = NULL;

Uint8 alpha = 255;

enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

bool init_game () {
  window = SDL_CreateWindow("qux", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

  // Init SDL_Image
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init(imgFlags) & imgFlags)) {
    printf("SDL_image could not initialize.");
    return false;
  }

  screen = SDL_GetWindowSurface(window);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

  if (renderer == NULL) {
    printf("Error creating renderer.");
    return false;
  }

  SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0xff, 0xff);

  return true;
}

SDL_Surface* load_surface (char* path) {
  /* SDL_Surface* optimized_surface = NULL; */
  SDL_Surface* surface = SDL_LoadBMP(path);
  if (surface == NULL) {
    printf("Cannot load surface %s. SDL_Error: %s\n", path, SDL_GetError());
  } else {

    // SDL_ConvertSurface appears to cause a segfault.
    /* optimized_surface = SDL_ConvertSurface(surface, screen->format, 0); */

    /* if (optimized_surface == NULL) { */
    /*   printf("Unable to optimize image. SDL_Error %s\n", SDL_GetError()); */
    /* } */
    /* SDL_FreeSurface(surface); */
    /* return optimized_surface; */
  }
  return surface;
}

SDL_Texture* load_texture (char* path) {
  SDL_Texture* new_texture = NULL;
  SDL_Surface* surface = IMG_Load(path);
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 255, 255));
  new_texture = SDL_CreateTextureFromSurface(renderer, surface);
  /* SDL_SetTextureColorMod(new_texture, 255, 255, 0); */
  SDL_FreeSurface(surface);
  return new_texture;
}

SDL_Surface* load_png (char* path) {
  SDL_Surface* surface = IMG_Load(path);
  return surface;
}

void draw_square () {
  SDL_Rect dest;
  dest.x = 0;
  dest.y = 0;
  dest.w = 100;
  dest.h = 300;
  SDL_BlitSurface(square, NULL, screen, NULL);
  /* SDL_BlitScaled(square, NULL, screen, &dest); */
}

void draw_shape () {
  SDL_Rect rect = {100, 100, 200, 200};
  SDL_SetRenderDrawColor(renderer, 0xff, 0, 0, 0xff);
  /* SDL_RenderFillRect(renderer, &rect); */
  /* SDL_RenderDrawRect(renderer, &rect); */
  /* SDL_RenderDrawLine(renderer, 0, 0, 400, 200); */
  for (int i=0; i < 200; i++) {
    SDL_Delay(10);
    SDL_RenderDrawLine(renderer, 0, 0, 640, i*8);
    SDL_Delay(10);
    SDL_RenderDrawLine(renderer, 0, i*8, 640, 0);
    SDL_RenderPresent(renderer);
  }
}

void draw_points () {
  for (int i=0; i < 256; i++) {
    SDL_SetRenderDrawColor(renderer, 0, i, 0, i);
    SDL_RenderDrawPoint(renderer, i, i);
    SDL_RenderDrawPoint(renderer, i, i + 1);
    SDL_RenderDrawPoint(renderer, i, i + 2);
    SDL_RenderDrawPoint(renderer, i, i + 3);
    SDL_RenderDrawPoint(renderer, i, i + 4);
    SDL_RenderDrawPoint(renderer, i, i + 5);
    SDL_RenderDrawPoint(renderer, i, i + 6);
    SDL_RenderDrawPoint(renderer, i, i + 7);
  }
}

void update_game () {
  screen = SDL_GetWindowSurface(window);
  /* SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff)); */
  /* draw_square(); */
  /* draw_shape(); */
  SDL_UpdateWindowSurface(window);
}

void loop_game () {
  // Blank screen
  screen = SDL_GetWindowSurface(window);

  /* SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff)); */
  SDL_RenderClear(renderer);
  /* draw_shape(); */
  /* draw_points(); */
  SDL_Rect viewport = {0, 0, 100, 100};
  /* SDL_RenderSetViewport(renderer, &viewport); */

  /* for (int i=0; i < 128; i++) { */
    /* SDL_SetTextureColorMod(colors, i, i*2, 255-i); */
    /* SDL_SetTextureColorMod(colors, 255, 0, 0); */
    /* SDL_RenderCopy(renderer, colors, NULL, NULL); */
    /* SDL_RenderPresent(renderer); */
    /* SDL_Delay(2); */
  /* } */

  bool should_quit = false;
  SDL_Event event;
  while (!should_quit) {
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        should_quit = true;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_UP:
          alpha = (alpha + 4) % 256;
          break;
        /*   SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00)); break; */
        case SDLK_DOWN:
          alpha = (alpha - 4) % 256;
          break;
        /*   SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0xff, 0x00)); break; */
        /* case SDLK_LEFT: */
        /*   SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff)); break; */
        /* case SDLK_RIGHT: */
        /*   SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0x00, 0xff)); break; */
        case SDLK_ESCAPE:
          should_quit = true; break;
        }
      }
    }

    /* SDL_SetTextureColorMod(colors, 128, 128, 128); */
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(colors, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(colors, alpha);
    /* SDL_RenderCopy(renderer, colors, NULL, NULL); */

    current_frame = (current_frame + 1) % 4;
    SDL_RenderCopy(renderer, person_texture, &sprite_rects[current_frame], NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(100);
    /* update_game(); */
  }
}

void quit_game () {
  SDL_DestroyTexture(colors);
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  IMG_Quit();
  SDL_Quit();
}

int main (int argc, char* args[]) {
  if (!init_game()) {
    return 1;
  }
  /* square = load_surface("./square.bmp"); */
  /* square = load_png("./rect.png"); */
  colors = load_texture("./colors.png");
  person_texture = load_texture("./person.png");
  sprite_rects[0].x = 0;
  sprite_rects[0].y = 0;
  sprite_rects[0].w = 64;
  sprite_rects[0].h = 205;
  sprite_rects[1].x = 64;
  sprite_rects[1].y = 0;
  sprite_rects[1].w = 64;
  sprite_rects[1].h = 205;
  sprite_rects[2].x = 128;
  sprite_rects[2].y = 0;
  sprite_rects[2].w = 64;
  sprite_rects[2].h = 205;
  sprite_rects[3].x = 196;
  sprite_rects[3].y = 0;
  sprite_rects[3].w = 64;
  sprite_rects[3].h = 205;
  loop_game();
  quit_game();
  return 0;
}
