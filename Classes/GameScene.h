#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "controllers/GameController.h"

class GameScene : public cocos2d::Scene
{
public:
    // 创建场景
    static cocos2d::Scene *createScene();
    // 初始化场景
    virtual bool init();
    CREATE_FUNC(GameScene);

    // 退出场景回调
    virtual void onExit();

private:
    GameController *_gameController;
};

#endif // __GAME_SCENE_H__
