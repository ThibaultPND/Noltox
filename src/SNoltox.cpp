#include "SNoltox.h"

Noltox::Noltox()
:   head(new body_t({320,320, 32, 32}, dir_t::RIGHT, 10, 10)),
    fruit(LoadTexture("img/food/kiwi.bmp"), 0, 0)
    {
        tail = head;
        this->headTx = LoadTexture("img/Noltox/head.bmp");
        this->bodyTx = LoadTexture("img/Noltox/body.bmp");
        
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                gameTab[i][j].tileType = tileType_t::none;
                gameTab[i][j].body = nullptr;
            }
        }
        gameTab[10][10].tileType = tileType_t::head;
        gameTab[10][10].body = head;

        do{
            fruit.x = rand()%20;
            fruit.y = rand()%20;
        } while (fruit.x == 320 && fruit.y == 320);
        
        SDL_QueryTexture(fruit.texture, NULL, NULL, &fruit.frame.w, &fruit.frame.h);
        fruit.frame.x = fruit.x*32;
        fruit.frame.y = fruit.y*32;
        renderFruit();
}
Noltox::~Noltox(){
    SDL_DestroyTexture(this->bodyTx);
    SDL_DestroyTexture(this->headTx);

    body_t* current = head;
    while (current != nullptr) {
        body_t* next = current->next;
        delete current;
        current = next;
    }

    SDL_DestroyTexture(fruit.texture);
}

void Noltox::render() {
    body_t *current = head->next;
    while (current != nullptr) {
        SDL_RenderCopyEx(
            gRenderer, bodyTx, NULL,
            &current->frame,
            static_cast<int>(current->direction),
            NULL, SDL_FLIP_NONE
        );
        current = current->next;
    }
    SDL_RenderCopyEx(
        gRenderer, headTx, NULL,
        &head->frame,
        static_cast<int>(head->direction),
        NULL, SDL_FLIP_NONE
    );
    
}

void Noltox::renderFruit() {
    SDL_RenderCopy(gRenderer, fruit.texture, NULL, &fruit.frame);
}

void Noltox::append() {
    body_t *newBody = new body_t(
        tail->frame,
        tail->direction,
        (tail->frame.y)/32,
        (tail->frame.x)/32
    );

    tail->next = newBody;
    newBody->prev = tail;
    tail = newBody;
}

void Noltox::append(body_t *importedBody) {
    body_t *newBody = new body_t(
        importedBody->frame,
        importedBody->direction,
        (importedBody->frame.y)/32,
        (importedBody->frame.x)/32
    );

    tail->next = newBody;
    newBody->prev = tail;
    tail = newBody;
}

int Noltox::crawl() {
    dir_t tempDirection = head->direction;
    switch (head->direction) {
        case dir_t::UP:
            if (head->frame.y <= 1 || isABodyForward(&head->frame, dir_t::UP)) {
                return 1;
            }
            head->frame.y -= 32;
            break;
        case dir_t::DOWN:
            if (head->frame.y >= 607 || isABodyForward(&head->frame, dir_t::DOWN)) {
                return 1;
            }
            head->frame.y += 32;
            break;
        case dir_t::LEFT:
            if (head->frame.x <= 1 || isABodyForward(&head->frame, dir_t::LEFT)) {
                return 1;
            }
            head->frame.x -= 32;
            break;
        case dir_t::RIGHT:
            if (head->frame.x >= 607 || isABodyForward(&head->frame, dir_t::RIGHT)) {
                return 1;
            }
            head->frame.x += 32;
            break;
    }
    body_t *current = head->next;
    while (current != nullptr) {
        switch (current->direction) {
            case dir_t::UP:
                current->frame.y -= 32;
                break;
            case dir_t::DOWN:
                current->frame.y += 32;
                break;
            case dir_t::LEFT:
                current->frame.x -= 32;
                break;
            case dir_t::RIGHT:
                current->frame.x += 32;
                break;
        }
        dir_t tempTempDirection = tempDirection;
        tempDirection = current->direction;
        current->direction = tempTempDirection;
        current = current->next;
    }

    return 0;
}

int Noltox::changerDirection(dir_t direction) {
    if (direction == head->direction) {
        return 0;
    }
    switch (direction) {
        case dir_t::UP:
            if (this->head->direction == dir_t::DOWN) {
                break;
            }
            this->head->direction = dir_t::UP;            
            break;
        case dir_t::DOWN:
            if (this->head->direction == dir_t::UP) {
                break;
            }
            this->head->direction = dir_t::DOWN;  
            break;
        case dir_t::LEFT:
            if (this->head->direction == dir_t::RIGHT) {
                break;
            }
            this->head->direction = dir_t::LEFT;  
            break;
        case dir_t::RIGHT:
            if (this->head->direction == dir_t::LEFT) {
                break;
            }
            this->head->direction = dir_t::RIGHT;  
            break;
    }
    return 1;
}
body_t *Noltox::getTail(){
    return this->tail;
}

bool Noltox::isABodyForward(SDL_Rect *frame, dir_t direction){
    body_t *current = head->next;
    while (current != nullptr) {
        switch (direction) {
            case dir_t::UP:
                if (current->prev->frame.x == frame->x
                &&  current->prev->frame.y == frame->y-32){
                    return true;
                }
                break;
            case dir_t::DOWN:
                if (current->prev->frame.x == frame->x
                &&  current->prev->frame.y == frame->y+32){
                    return true;
                }
                break;
            case dir_t::LEFT:
                if (current->prev->frame.x == frame->x-32
                &&  current->prev->frame.y == frame->y){
                    return true;
                }
                break;
            case dir_t::RIGHT:
                if (current->prev->frame.x == frame->x+32
                &&  current->prev->frame.y == frame->y){
                    return true;
                }
                break;
        }
        
        current = current->next;
    }
    return false;
}

dir_t Noltox::getDirection(){
    return this->head->direction;
}
void Noltox::setDirection(dir_t direction) {
    this->head->direction = direction;
}

// case dir_t::UP:
//     break;
// case dir_t::DOWN:
//     break;
// case dir_t::LEFT:
//     break;
// case dir_t::RIGHT:
//     break;