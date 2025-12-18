#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "managers/UndoManager.h"

class GameController
{
public:
    GameController();
    ~GameController();

    // 初始化控制器
    void init(cocos2d::Scene *scene);
    // 开始游戏，默认第一关
    void startGame(int levelId = 1);

    // Interaction handlers
    // 卡牌点击回调
    void onCardClicked(int cardId);
    // 备用牌堆点击回调
    void onReserveClicked();
    // 撤回按钮点击回调
    void onUndoClicked();

    // 重玩按钮点击回调
    void onReplayClicked();
    // 下一关按钮点击回调
    void onNextLevelClicked();
    // 关闭游戏按钮点击回调
    void onCloseGameClicked();

private:
    GameModel *_gameModel;
    GameView *_gameView;
    UndoManager *_undoManager;
    int _currentLevelId;

    // 更新视图
    void updateView();
    // 更新卡牌翻面状态
    void updateFaceUpState();
    // 判断卡牌是否可匹配
    bool canMatch(CardModel *card, CardModel *target);
    // 检查胜利条件
    void checkWinCondition();
};

#endif
