//
// Created by v on 12.12.2018.
//

#ifndef SDL2_E_GAMESTATEMACHINE_H
#define SDL2_E_GAMESTATEMACHINE_H

#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
    GameStateMachine();
    ~GameStateMachine();

    void pushState(GameState* state);
    void changeState(GameState* state);
    void popState();


    void update();
    void render();
    void playSound();


private:
    std::vector<GameState*> gameStates;
    std::vector<GameState*> gameStatesForDelete;

};

#endif //SDL2_E_GAMESTATEMACHINE_H
