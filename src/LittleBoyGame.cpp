#include <stdio.h>
#include <ViewRenderer.h>
#include <InputEventHandler.h>
#include <Game.h>
#include <Sprite.h>

using namespace std;

void loadResource()
{

}

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
            case MV_U:
                game.movePlayer(0);
                break;
            case MV_R:
                game.movePlayer(1);
                break;
            case MV_D:
                game.movePlayer(2);
                break;
            case MV_L:
                game.movePlayer(3);
                break;
            } 
            game.update();
            game.render(viewRenderer);
            int endLoop = SDL_GetTicks() - startLoop;
            if (endLoop < delay) 
            {
                SDL_Delay(delay - endLoop);
            }
        }
    }
   
    //Free resources and close SDL
    ViewRenderer::clearInstance();
    SpriteRegister::clearInstance();
    delete inputHandler;
    inputHandler = NULL;
    return 0;
}
