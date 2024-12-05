#include <stdio.h>
#include <ViewRenderer.h>
#include <InputEventHandler.h>
#include <Game.h>

using namespace std;

int main(int argc, char* argv[]) {
    ViewRenderer* viewRenderer = ViewRenderer::getInstance();
    EventHandler* inputHandler = new InputEventHandler();

    //Start up SDL and create window
    if (!viewRenderer->init(600, 600))
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        
        Game game = Game();
        
        bool quit = false;
        int delay = 1000 / 20;
  
        while (!quit)
        {
            // adjust speed here
            
            int startLoop = SDL_GetTicks();
            EventHandleResult res = inputHandler->handle();
            switch (res.code) 
            {
            case QUIT:
                quit = true;
                break;
            } 
            game.update();
            int endLoop = SDL_GetTicks() - startLoop;
            if (endLoop < delay) 
            {
                SDL_Delay(delay - endLoop);
            }
        }
        game.clear();
    }
   
    //Free resources and close SDL
    ViewRenderer::clearInstance();
    TileFactory::clearInstance();
    delete inputHandler;
    inputHandler = NULL;
    return 0;
}
