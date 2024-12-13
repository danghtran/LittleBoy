#include <ViewRenderer.h>
#include <iostream>


bool ViewRenderer::init(int w, int h)
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

void ViewRenderer::render(SDL_Texture*& texture)
{
    //Render texture to screen
    SDL_RenderCopy(gRenderer, texture, NULL, NULL);

    //Update screen
    SDL_RenderPresent(gRenderer);
}

void ViewRenderer::close()
{
    //Deallocate renderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;

    //Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* ViewRenderer::loadTexture(std::string path)
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        // Color Keying
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

void ViewRenderer::renderSprite(SDL_Texture* texture, SDL_Rect* spriteRect, SDL_Rect* renderRect)
{
    SDL_RenderCopy(gRenderer, texture, spriteRect, renderRect);
}

void ViewRenderer::commitChange()
{
    SDL_RenderPresent(gRenderer);
}

ViewRenderer::ViewRenderer()
{
}

ViewRenderer::~ViewRenderer()
{
    close();
}

// Singleton
ViewRenderer* ViewRenderer::instance;

ViewRenderer* ViewRenderer::getInstance()
{
    if (instance == NULL)
    {
        instance = new ViewRenderer();
    }
    return instance;
}

void ViewRenderer::clearInstance()
{
    delete instance;
    instance = NULL;
}