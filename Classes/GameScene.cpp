#include "GameScene.h"

USING_NS_CC;

Scene *GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _gameController = new GameController();
    _gameController->init(this);
    _gameController->startGame();

    return true;
}

void GameScene::onExit()
{
    if (_gameController)
    {
        delete _gameController;
        _gameController = nullptr;
    }
    Scene::onExit();
}
