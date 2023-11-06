#ifndef __TXUTILS_H__
    #define __TXUTILS_H__

    #include <iostream>
    #include <SDL2/SDL.h>
    #include "GlobalRenderer.h"

    SDL_Texture *LoadTexture ( const char *path );
    SDL_Texture *LoadingTextureAndRect ( const char *path, SDL_Rect &rect, Uint16 x = 0, Uint16 y = 0 );
    void LoadRectFromTexture ( SDL_Texture *texture, SDL_Rect &rect, Uint16 x = 0, Uint16 y = 0 );

#endif // __TXUTILS__H_