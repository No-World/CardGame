#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "configs/GameConfig.h"
#include "cocos2d.h"

/**
 * CardModel
 * 运行时动态数据模型 - 卡牌
 */
class CardModel
{
public:
    CardModel();
    ~CardModel();

    // 初始化卡牌数据
    void init(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2 &position);

    // 获取卡牌ID
    int getId() const { return _id; }
    // 获取卡牌点数
    CardFaceType getFace() const { return _face; }
    // 获取卡牌花色
    CardSuitType getSuit() const { return _suit; }
    // 获取卡牌位置
    const cocos2d::Vec2 &getPosition() const { return _position; }

    // 设置卡牌翻面状态
    void setFaceUp(bool faceUp) { _isFaceUp = faceUp; }
    // 卡牌是否正面朝上
    bool isFaceUp() const { return _isFaceUp; }

    // 设置卡牌位置
    void setPosition(const cocos2d::Vec2 &pos) { _position = pos; }

private:
    int _id;
    CardFaceType _face;
    CardSuitType _suit;
    cocos2d::Vec2 _position;
    bool _isFaceUp;
};

#endif // __CARD_MODEL_H__
