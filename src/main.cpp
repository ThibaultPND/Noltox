/***************************************************************
**  Auteur : Thibault Chassagne
**  MAJ : 01/11/23
*  
**  Nom : Snake
*  
*?  Description : Ce logiciel à pour but de crée le jeu SNAKE en utilisant la librairie graphique
*?                SDL2 (librairie C).
*
g++ -o prog -Iinclude -Iinclude/SDL2 src/*.cpp -Llib -lSDL2main -lSDL2 -static -DSDL_MAIN_HANDLED && bin\monProgramme.exe
***************************************************************/
#include <Project.h>
#include <SDL2/SDL.h>
#include "TxUtils.h"
#include "GlobalRenderer.h"
#include "background.h"
#include "SNoltox.h"


int main(int argc, char* argv[]) {
    std::cout << "Debut du  programme...\n" << std::endl;
    try {
        // Initialisation
        project::Application app;
        srand(SDL_GetTicks());

        // Programme

        background fond;
        fond.render();
        Noltox serpent;
        serpent.render();
        
        SDL_RenderPresent(gRenderer);


        // Boucle
        int nextTurn = -1;
        bool waitTurn = false;
        bool waitAppend = false;
        Uint32 avancerTimer = SDL_GetTicks();
        bool programLaunched(true);
        while (programLaunched) {
            if ((SDL_GetTicks() - avancerTimer) > 350) {
                if (waitAppend) {
                    body_t *newBody = new body_t(
                        serpent.getTail()->frame,
                        serpent.getTail()->direction,
                        (serpent.getTail()->frame.y)/32,
                        (serpent.getTail()->frame.x)/32
                    );
                    if(serpent.crawl()){
                        programLaunched = false;
                        continue;
                    }else {
                        serpent.append(newBody);
                        fond.render();
                        serpent.render();
                        serpent.renderFruit();
                        SDL_RenderPresent(gRenderer);
                    }
                    waitAppend = false;
                } else {
                    if(serpent.crawl()){
                        programLaunched = false;
                        continue;
                    }else {
                        fond.render();
                        serpent.render();
                        serpent.renderFruit();
                        SDL_RenderPresent(gRenderer);
                    }
                }
                waitTurn = false;
                avancerTimer = SDL_GetTicks();
            }
            

            SDL_Event event;
            while(SDL_PollEvent(&event)) {
                switch(event.type){
                    case SDL_QUIT:
                        programLaunched = false;
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym){
                            case SDLK_UP:
                                if (waitTurn){
                                    if (serpent.getDirection() != dir_t::UP){
                                        nextTurn = static_cast<int>(dir_t::UP);
                                    }
                                    
                                    break;
                                }
                                if (serpent.changerDirection(dir_t::UP)) {
                                    serpent.render();
                                    SDL_RenderPresent(gRenderer);
                                }
                                if (nextTurn != -1){
                                    serpent.setDirection(dir_t::UP);
                                }
                                waitTurn = true;
                                break;
                            case SDLK_DOWN:
                                if (waitTurn){
                                    if (serpent.getDirection() != dir_t::DOWN){
                                        nextTurn = static_cast<int>(dir_t::DOWN);
                                    }
                                    
                                    break;
                                }
                                if (serpent.changerDirection(dir_t::DOWN)) {
                                    serpent.render();
                                    SDL_RenderPresent(gRenderer);
                                }
                                if (nextTurn != -1){
                                    serpent.setDirection(dir_t::DOWN);
                                }
                                waitTurn = true;
                                break;
                            case SDLK_LEFT:
                                if (waitTurn){
                                    if (serpent.getDirection() != dir_t::LEFT){
                                        nextTurn = static_cast<int>(dir_t::LEFT);
                                    }
                                    
                                    break;
                                }
                                if (serpent.changerDirection(dir_t::LEFT)) {
                                    serpent.render();
                                    SDL_RenderPresent(gRenderer);
                                }
                                if (nextTurn != -1){
                                    serpent.setDirection(dir_t::LEFT);
                                }
                                waitTurn = true;
                                break;
                            case SDLK_RIGHT:
                                if (waitTurn){
                                    if (serpent.getDirection() != dir_t::RIGHT){
                                        nextTurn = static_cast<int>(dir_t::RIGHT);
                                    }
                                    
                                    break;
                                }
                                if (serpent.changerDirection(dir_t::RIGHT)) {
                                    serpent.render();
                                    SDL_RenderPresent(gRenderer);
                                }
                                if (nextTurn != -1){
                                    serpent.setDirection(dir_t::RIGHT);
                                }
                                waitTurn = true;
                                break;
                            case SDLK_SPACE:
                                serpent.crawl();
                                fond.render();
                                serpent.render();
                                serpent.renderFruit();
                                SDL_RenderPresent(gRenderer);
                                break;
                            case SDLK_r:
                                waitAppend = true;
                        }
                        break;
                }
            }
            SDL_Delay(16);
        }

        

    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale dans le programme principal : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    
    std::cout << "Fin du programme...\n" << std::endl;

    return EXIT_SUCCESS;
}