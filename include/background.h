#if !defined(__BACKGROUND_H__)
    #define __BACKGROUND_H__

    #include <SDL2/SDL.h>
    #include "TxUtils.h"
    #include "GlobalRenderer.h"

    class background {
        private:
            SDL_Texture *texture;
            SDL_Rect frame;
        public:
            background();
            void render();
            ~background();
    };
    


#endif // __BACKGROUND_H__
