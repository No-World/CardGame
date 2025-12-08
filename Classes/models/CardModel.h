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

    void init(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2 &position);

    int getId() const { return _id; }
    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    const cocos2d::Vec2 &getPosition() const { return _position; }

    void setFaceUp(bool faceUp) { _isFaceUp = faceUp; }
    bool isFaceUp() const { return _isFaceUp; }

    void setPosition(const cocos2d::Vec2 &pos) { _position = pos; }

private:
    int _id;
    CardFaceType _face;
    CardSuitType _suit;
    cocos2d::Vec2 _position;
    bool _isFaceUp;
};

#endif // __CARD_MODEL_H__
