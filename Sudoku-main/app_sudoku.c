#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>
#include "generateur_sudoku.h"

#define GRID_SIZE 9
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

typedef struct {
    int value;
    bool candidates[9];
} Cell;

Cell board[GRID_SIZE][GRID_SIZE];
bool mode_annotation = false;

int hover_i = -1, hover_j = -1; // case survolée par la souris

void print_board() {
    printf("\nSudoku actuel:\n");
    for(int i=0;i<GRID_SIZE;i++){
        for(int j=0;j<GRID_SIZE;j++){
            printf("%d ", board[i][j].value);
        }
        printf("\n");
    }
}

void draw_cell(SDL_Renderer *renderer, TTF_Font *font, int i, int j, int cellWidth, int cellHeight) {
    SDL_Rect rect = { j*cellWidth + BUTTON_WIDTH, i*cellHeight, cellWidth, cellHeight };

    // Fond de la case
    if(i == hover_i && j == hover_j){
        SDL_SetRenderDrawColor(renderer, 220,220,220,255); // gris clair pour survol
    } else {
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    }
    SDL_RenderFillRect(renderer,&rect);

    // Bord de la case
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderDrawRect(renderer,&rect);

    Cell c = board[i][j];

    if(c.value != 0){
        char str[2]; sprintf(str,"%d",c.value);
        SDL_Color color = {0,0,0,255};
        SDL_Surface *surface = TTF_RenderText_Solid(font,str,color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
        SDL_Rect dst = { rect.x + (cellWidth - surface->w)/2, rect.y + (cellHeight - surface->h)/2, surface->w, surface->h };
        SDL_RenderCopy(renderer,texture,NULL,&dst);
        SDL_FreeSurface(surface); SDL_DestroyTexture(texture);
    } else {
        SDL_Color color = {180,180,180,255};
        for(int k=0;k<9;k++){
            if(c.candidates[k]){
                char str[2]; sprintf(str,"%d",k+1);
                SDL_Surface *surface = TTF_RenderText_Solid(font,str,color);
                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
                int sub_x = k%3;
                int sub_y = k/3;
                SDL_Rect dst = {
                    rect.x + sub_x*(cellWidth/3) + (cellWidth/3 - surface->w)/2,
                    rect.y + sub_y*(cellHeight/3) + (cellHeight/3 - surface->h)/2,
                    surface->w, surface->h
                };
                SDL_RenderCopy(renderer,texture,NULL,&dst);
                SDL_FreeSurface(surface); SDL_DestroyTexture(texture);
            }
        }
    }
}

// Dessine la grille et les boutons
void draw_modern_button(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect rect, const char* text, bool active, bool hover) {
    // Ombre
    SDL_Rect shadow = rect;
    shadow.x += 3; shadow.y += 3;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 80);
    SDL_RenderFillRect(renderer, &shadow);

    // Dégradé horizontal simulé
    for(int y=0;y<rect.h;y++){
        float t = (float)y/rect.h;
        Uint8 r = (Uint8)((active ? 50 : 180)*(1-t) + (active ? 100 : 220)*t);
        Uint8 g = (Uint8)((active ? 50 : 180)*(1-t) + (active ? 100 : 220)*t);
        Uint8 b = (Uint8)((active ? 50 : 180)*(1-t) + (active ? 100 : 220)*t);
        SDL_SetRenderDrawColor(renderer,r,g,b,255);
        SDL_RenderDrawLine(renderer,rect.x,rect.y+y,rect.x+rect.w-1,rect.y+y);
    }

    // Bordure arrondie simulée
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer,&rect);

    // Texte
    SDL_Color textColor = {255,255,255,255};
    if(hover) textColor = (SDL_Color){230,230,230,255};
    SDL_Surface *surf = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_Rect dst = { rect.x + (rect.w - surf->w)/2, rect.y + (rect.h - surf->h)/2, surf->w, surf->h };
    SDL_RenderCopy(renderer,tex,NULL,&dst);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);
}



void draw(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    int cellWidth = (WINDOW_WIDTH - BUTTON_WIDTH) / GRID_SIZE;
    int cellHeight = WINDOW_HEIGHT / GRID_SIZE;

    // Dessine les cases
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            SDL_Rect rect = { j * cellWidth + BUTTON_WIDTH, i * cellHeight, cellWidth, cellHeight };

            // Survol de la souris
            if (i == hover_i && j == hover_j) {
                SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
                SDL_RenderFillRect(renderer, &rect);
            }

            draw_cell(renderer, font, i, j, cellWidth, cellHeight);
        }
    }

    // Lignes de la grille
    for (int i = 0; i <= GRID_SIZE; i++) {
        int thickness = (i % 3 == 0) ? 3 : 1;
        SDL_SetRenderDrawColor(renderer, (i % 3 == 0) ? 0 : 100, (i % 3 == 0) ? 0 : 100, (i % 3 == 0) ? 0 : 100, 255);
        for (int t = 0; t < thickness; t++) {
            SDL_RenderDrawLine(renderer, BUTTON_WIDTH, i * cellHeight + t, WINDOW_WIDTH, i * cellHeight + t);
            SDL_RenderDrawLine(renderer, BUTTON_WIDTH + i * cellWidth + t, 0, BUTTON_WIDTH + i * cellWidth + t, WINDOW_HEIGHT);
        }
    }

    // Boutons
    SDL_Rect btnTry = {5, 50, BUTTON_WIDTH - 10, BUTTON_HEIGHT};
    SDL_Rect btnWrite = {5, 150, BUTTON_WIDTH - 10, BUTTON_HEIGHT};

    // Gestion survol souris
    int mx, my;
    Uint32 mouseState = SDL_GetMouseState(&mx, &my);
    bool hoverTry = SDL_PointInRect(&(SDL_Point){mx, my}, &btnTry);
    bool hoverWrite = SDL_PointInRect(&(SDL_Point){mx, my}, &btnWrite);

    draw_modern_button(renderer, font, btnTry, "try", mode_annotation, hoverTry);
    draw_modern_button(renderer, font, btnWrite, "write", !mode_annotation, hoverWrite);


    SDL_RenderPresent(renderer);
}


int main(int argc,char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){ printf("Erreur SDL: %s\n",SDL_GetError()); return 1; }
    if(TTF_Init()==-1){ printf("Erreur TTF: %s\n",TTF_GetError()); SDL_Quit(); return 1; }

    SDL_Window *window = SDL_CreateWindow("Sudoku",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    TTF_Font *font = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf",26);

    // Génération de la grille initiale
    int matrice[GRID_SIZE][GRID_SIZE]={0};
    remplir_grille(matrice);
    affiche_grille_level(matrice,"facile");

    for(int i=0;i<GRID_SIZE;i++)
        for(int j=0;j<GRID_SIZE;j++){
            board[i][j].value = matrice[i][j];
            for(int n=0;n<9;n++) board[i][j].candidates[n]=false;
        }

    int selected_i=-1, selected_j=-1;
    SDL_Event event;
    bool running = true;

    while(running){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: running=false; break;

                case SDL_MOUSEMOTION:
                    hover_i = -1; hover_j = -1;
                    int mx = event.motion.x, my = event.motion.y;
                    if(mx>=BUTTON_WIDTH){
                        int cellWidth = (WINDOW_WIDTH - BUTTON_WIDTH)/GRID_SIZE;
                        int cellHeight = WINDOW_HEIGHT/GRID_SIZE;
                        hover_j = (mx - BUTTON_WIDTH)/cellWidth;
                        hover_i = my/cellHeight;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:{
                    int mx = event.button.x, my = event.button.y;
                    if(mx>=5 && mx<=BUTTON_WIDTH-5 && my>=50 && my<=50+BUTTON_HEIGHT){ mode_annotation=true; break; }
                    if(mx>=5 && mx<=BUTTON_WIDTH-5 && my>=150 && my<=150+BUTTON_HEIGHT){ mode_annotation=false; break; }

                    int cellWidth = (WINDOW_WIDTH - BUTTON_WIDTH)/GRID_SIZE;
                    int cellHeight = WINDOW_HEIGHT/GRID_SIZE;
                    if(mx>=BUTTON_WIDTH){
                        selected_j = (mx - BUTTON_WIDTH)/cellWidth;
                        selected_i = my/cellHeight;
                    }
                    break;
                }

                case SDL_KEYDOWN:
                    if(selected_i>=0 && selected_j>=0){
                        int k=-1;
                        if(event.key.keysym.sym>=SDLK_1 && event.key.keysym.sym<=SDLK_9) k = event.key.keysym.sym - SDLK_0;
                        else if(event.key.keysym.sym==SDLK_0 || event.key.keysym.sym==SDLK_BACKSPACE) k=0;

                        if(k!=-1){
                            if(mode_annotation){
                                if(k==0){
                                    for(int n=0;n<9;n++) board[selected_i][selected_j].candidates[n]=false;
                                } else {
                                    board[selected_i][selected_j].candidates[k-1]=true;
                                }
                            } else {
                                board[selected_i][selected_j].value=k;
                                for(int n=0;n<9;n++) board[selected_i][selected_j].candidates[n]=false;
                                print_board();
                            }
                        }
                    }
                    break;
            }
        }
        draw(renderer,font);
        SDL_Delay(50);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
