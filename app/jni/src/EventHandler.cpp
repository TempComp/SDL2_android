//
// Created by v on 09.12.2018.
//

#include "EventHandler.h"
#include "Game.h"

EventHandler::EventHandler()
{
    fingerEventKind.reserve(6);

    fingerEventKind.push_back(false);
    fingerEventKind.push_back(false);
    fingerEventKind.push_back(false);
    fingerEventKind.push_back(false);
    fingerEventKind.push_back(false);
    fingerEventKind.push_back(false);
}

EventHandler::~EventHandler()
{
    fingerEventKind.clear();
}

void EventHandler::updateEventHandler()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
//MOBILE APP LIFECYCLE
            //The application is low on memory, free memory if possible.
            // Called on iOS in applicationDidReceiveMemoryWarning()
            //Called on Android in onLowMemory()
            case SDL_APP_LOWMEMORY:

                SDL_Log("EventHandler switch(event.type) : SDL_APP_LOWMEMORY");
                break;

            //Prepare for go to background. Can terminated without event.
            // Prepare for potential terminating here !!!!
            // Called on iOS in applicationWillResignActive()
            // Called on Android in onPause()
            case SDL_APP_WILLENTERBACKGROUND:
                //Game::instance()->endGame(); or save game

                SDL_Log("EventHandler switch(event.type) : SDL_APP_WILLENTERBACKGROUND");
                break;

            //already in background
            //Called on iOS in applicationDidEnterBackground()
            //Called on Android in onPause()
            case SDL_APP_DIDENTERBACKGROUND:

                SDL_Log("EventHandler switch(event.type) : SDL_APP_DIDENTERBACKGROUND");
                break;

            //prepare to appear in foreground
            //Called on iOS in applicationWillEnterForeground()
            //Called on Android in onResume()
            case SDL_APP_WILLENTERFOREGROUND:

                SDL_Log("EventHandler switch(event.type) : SDL_APP_WILLENTERFOREGROUND");
                break;

            //already in foreground
            //Called on iOS in applicationDidBecomeActive()
            //Called on Android in onResume()
            case SDL_APP_DIDENTERFOREGROUND:
                SDL_Log("EventHandler switch(event.type) : SDL_APP_DIDENTERFOREGROUND");

                break;
// ENDMOBILE APP LIFECYCLE

            //close window
            case SDL_QUIT:
                SDL_Log("EventHandler switch(event.type) : SDL_QUIT");
                Game::instance()->endGame();
                break;

//KEYS
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_AC_BACK)
                {
                    SDL_Log("EventHandler Application control keypad : SDL_SCANCODE_AC_BACK");
                }

                SDL_Log("EventHandler switch(event.type) : SDL_KEYDOWN");
                break;

            case SDL_KEYUP:
                if(event.key.keysym.scancode == SDL_SCANCODE_AC_BACK)
                {
                    SDL_Log("EventHandler Application control keypad : SDL_SCANCODE_AC_BACK");
                }

                SDL_Log("EventHandler switch(event.type) : SDL_KEYUP");
                break;
//END KEYS

//TOUCH EVENT
            case SDL_FINGERDOWN:
                fingerEventKind[FINGER_DOWN] = true;
                fingerEventKind[FINGER_UP] = false;

                timeFingerDown = SDL_GetTicks();

                fingerDownPos.x = event.tfinger.x * Game::instance()->getScreenWidth();
                fingerDownPos.y = event.tfinger.y * Game::instance()->getScreenHeight();

                break;

            case SDL_FINGERUP:
                fingerEventKind[FINGER_UP] = true;
                fingerEventKind[FINGER_DOWN] = false;
                fingerEventKind[FINGER_MOTION] = false;

                if(SDL_GetTicks() < timeFingerDown + timeFastTouch)
                {
                    fingerEventKind[FINGER_DOWN_FAST_UP] = true;
                }

                fingerUpPos.x = event.tfinger.x * Game::instance()->getScreenWidth();
                fingerUpPos.y = event.tfinger.y * Game::instance()->getScreenHeight();
                break;

            case SDL_FINGERMOTION:
                fingerEventKind[FINGER_MOTION] = true;

                fingerMotionPos.x = event.tfinger.x * Game::instance()->getScreenWidth();
                fingerMotionPos.y = event.tfinger.y * Game::instance()->getScreenHeight();
                break;
//END TOUCH EVENT

//SCREEN
            case SDL_WINDOWEVENT :
                if(SDL_GetDisplayOrientation(0) == SDL_ORIENTATION_LANDSCAPE )
                {
                    //SDL_Log("SDL_ORIENTATION_LANDSCAPE");
                }

                break;

//END SCREEN

        }
    }

}

void EventHandler::resetFingerEvents() {

    fingerEventKind[FINGER_DOWN] = false;
    fingerEventKind[FINGER_UP] = false;
    fingerEventKind[FINGER_MOTION] = false;
    fingerEventKind[FINGER_DOWN_FAST_UP] = false;
}