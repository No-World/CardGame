#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "controllers/GameController.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

    virtual void onExit();

private:
    GameController *_gameController;
};

#endif // __GAME_SCENE_H__
