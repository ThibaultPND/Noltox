#include "background.h"

background::background(){
    this->texture =  LoadingTextureAndRect("img/background.bmp", this->frame);
    std::cout << "[+] Background" << std::endl;
}
background::~background(){
    SDL_DestroyTexture(this->texture);
    std::cout << "[-] Background" << std::endl;
}
void background::render(){
    SDL_RenderCopy(gRenderer, texture, NULL, &frame);
}