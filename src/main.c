#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
 
//--------------------------------------

void SDL_ExitWithError(char *message);
int SDL_DrawColor(SDL_Renderer *renderer, SDL_Color *color);
void pause();
//--------------------------------------

int main(int argc, char *argv[])
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect rects[50];
    SDL_Color blanc = {255, 255, 255, 255};
//--------------------------------------
    //Création Damier :
    size_t i = 0;
    for(i = 0; i < 50; i++)
    {   
        rects[i].w = 50;
        rects[i].h = 50;
        rects[i].x = 100 * (i % 5) + 50 * ((i / 5) % 2);
        rects[i].y = 50 * (i / 5);
    }
//--------------------------------------

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_ExitWithError("Initialisation SDL");
    }
    
    if (SDL_CreateWindowAndRenderer( 500, 500, 0, &window, &renderer) != 0)
    {
        SDL_ExitWithError("Impossible de crée la fenêtre et du rendu, veuillez réessayer");
    }
    if (SDL_DrawColor(renderer,&blanc ) != 0)
    {
        SDL_ExitWithError("Impossible de crée la couleur");
    }

    if (SDL_RenderFillRects(renderer, rects , 50) != 0)
    {
        SDL_ExitWithError("Erreur Création Damier");
    }
//--------------------------------------

    SDL_SetWindowTitle(window, "Damier Simple");
    SDL_RenderPresent(renderer);
//--------------------------------------
    pause();
//--------------------------------------
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit(); 
    return EXIT_SUCCESS; 
}
//--------------------------------------
void pause()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int SDL_DrawColor(SDL_Renderer *renderer, SDL_Color *color){
    if(0 != SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a))
    {
        return -1;
    }
    return 0;
}

void SDL_ExitWithError(char *message){
    SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
