#include"Project.h"

namespace project
{
Application::Application(){

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error("Erreur lors de l'initialisation de SDL : " + std::string(SDL_GetError()));
    }

    // Création de la fenêtre
    gWindow = SDL_CreateWindow("MonProgramme", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);
    if (gWindow == nullptr) {
        SDL_Quit();
        throw std::runtime_error("Erreur lors de la création de la fenêtre : " + std::string(SDL_GetError()));
    }

    // Création du rendu
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
    if (gRenderer == nullptr) {
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        throw std::runtime_error("Erreur lors de la création du rendu : " + std::string(SDL_GetError()));
    }
}

Application::~Application() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    std::cout << "Application détruite !" << std::endl;
}
} // namespace project


void ExitWithError(const char *message){
    SDL_Log("Erreur : %s > %s", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

