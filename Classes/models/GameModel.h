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

    // 添加桌面卡牌
    void addPlayfieldCard(CardModel *card);
    // 添加堆叠卡牌
    void addStackCard(CardModel *card);
    // 添加备用卡牌
    void addReserveCard(CardModel *card);

    // 获取桌面卡牌列表
    const std::vector<CardModel *> &getPlayfieldCards() const { return _playfieldCards; }
    // 获取堆叠卡牌列表
    const std::vector<CardModel *> &getStackCards() const { return _stackCards; }
    // 获取备用卡牌列表
    const std::vector<CardModel *> &getReserveCards() const { return _reserveCards; }

    // 根据ID获取卡牌
    CardModel *getCardById(int id);

    // Operations
    // 移动卡牌到堆叠区
    void moveCardToStack(int cardId); // Move from Playfield to Stack top
    // 从备用牌堆抽取卡牌
    CardModel *drawFromReserve();     // Move from Reserve to Stack

    // 获取堆叠区顶部卡牌
    CardModel *getTopStackCard();
    // 获取备用牌堆顶部卡牌
    CardModel *getTopReserveCard();

    // For Undo
    // 恢复卡牌到桌面（撤回用）
    void restoreCardToPlayfield(int cardId, const cocos2d::Vec2 &pos);
    // 撤回从备用牌堆抽取的操作
    void undoDrawFromReserve(); // Move top stack back to reserve

private:
    std::vector<CardModel *> _playfieldCards;
    std::vector<CardModel *> _stackCards;
    std::vector<CardModel *> _reserveCards;
};

#endif // __GAME_MODEL_H__
