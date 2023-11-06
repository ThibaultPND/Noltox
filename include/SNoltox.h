#if !defined(__NOLTOX_H__)
    #define __NOLTOX_H__

    #include <SDL2/SDL.h>
    #include "TxUtils.h"
    #include "GlobalRenderer.h"

    enum class dir_t { 
        UP = 180,
        DOWN = 0,
        RIGHT = 270,
        LEFT = 90
    };
    enum class tileType_t{ none, body, head, fruit};

    struct body_t{
        SDL_Rect frame;

        dir_t direction;

        int y;
        int x;

        body_t *prev;
        body_t *next;

        body_t(const SDL_Rect& rect, dir_t dir, int col, int row, body_t* prv = nullptr, body_t* nxt = nullptr)
        : frame(rect), direction(dir),y(col), x(row), prev(prv), next(nxt) {}
    };

    typedef struct {
        tileType_t tileType;
        body_t *body;
    }gameTab;

    class Noltox {
        private:
            SDL_Texture *headTx;
            SDL_Texture *bodyTx;
            int lenght = 0;

            gameTab gameTab[20][20];

            body_t *head;
            body_t *tail;

        public:
            Noltox();
            int changerDirection(dir_t direction);
            void render();
            void append();
            void append(body_t *importedBody);
            int crawl();
            body_t *getTail();
            bool isABodyForward(SDL_Rect *frame, dir_t direction);
            ~Noltox();
    };
    

#endif // __NOLTOX_H__
