#include <SDL.h>
#include <InputEventHandler.h>

InputEventHandler::InputEventHandler() {}

InputEventHandler::~InputEventHandler() {}

EventHandleResult InputEventHandler::handle()
{
    SDL_Event event;
    EventHandleResult res = EventHandleResult();
    //Handle events on queue
    while (SDL_PollEvent(&event) != 0)
    {
        
        if (event.type == SDL_QUIT)
        {
            res.code = QUIT;
            break;
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                res.code = MV_U;
                break;
            case SDLK_DOWN:
                res.code = MV_D;
                break;
            case SDLK_LEFT:
                res.code = MV_L;
                break;
            case SDLK_RIGHT:
                res.code = MV_R;
                break;
            case SDLK_r:
                res.code = RESTART;
                break;
            case SDLK_s:
                res.code = START;
            default:
                break;
            }
        }
    }
    return res;
}