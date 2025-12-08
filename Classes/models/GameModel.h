#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include <vector>
#include "CardModel.h"

/**
 * GameModel
 * 运行时动态数据模型 - 游戏整体数据
 */
class GameModel
{
public:
    GameModel();
    ~GameModel();

    void addPlayfieldCard(CardModel *card);
    void addStackCard(CardModel *card);
    void addReserveCard(CardModel *card);

    const std::vector<CardModel *> &getPlayfieldCards() const { return _playfieldCards; }
    const std::vector<CardModel *> &getStackCards() const { return _stackCards; }
    const std::vector<CardModel *> &getReserveCards() const { return _reserveCards; }

    CardModel *getCardById(int id);

    // Operations
    void moveCardToStack(int cardId); // Move from Playfield to Stack top
    CardModel *drawFromReserve();     // Move from Reserve to Stack

    CardModel *getTopStackCard();

    // For Undo
    void restoreCardToPlayfield(int cardId, const cocos2d::Vec2 &pos);
    void undoDrawFromReserve(); // Move top stack back to reserve

private:
    std::vector<CardModel *> _playfieldCards;
    std::vector<CardModel *> _stackCards;
    std::vector<CardModel *> _reserveCards;
};

#endif // __GAME_MODEL_H__
