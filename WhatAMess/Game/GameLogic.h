#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <glm/glm.hpp>

class GameLogic
{
public:
    GameLogic();
    bool Init();
    void Update();
    void CleanUp();

private:
    void CreateRing(glm::vec2 position);
    bool prevButton = false;
};

#endif
