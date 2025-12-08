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

    void init(cocos2d::Scene *scene);
    void startGame(int levelId = 1);

    // Interaction handlers
    void onCardClicked(int cardId);
    void onReserveClicked();
    void onUndoClicked();

    void onReplayClicked();
    void onNextLevelClicked();
    void onCloseGameClicked();

private:
    GameModel *_gameModel;
    GameView *_gameView;
    UndoManager *_undoManager;
    int _currentLevelId;

    void updateView();
    void updateFaceUpState();
    bool canMatch(CardModel *card, CardModel *target);
    void checkWinCondition();
};

#endif
