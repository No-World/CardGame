#include "CardModel.h"

CardModel::CardModel()
    : _id(-1), _face(CFT_NONE), _suit(CST_NONE), _position(cocos2d::Vec2::ZERO), _isFaceUp(false)
{
}

CardModel::~CardModel()
{
}

void CardModel::init(int id, CardFaceType face, CardSuitType suit, const cocos2d::Vec2 &position)
{
    _id = id;
    _face = face;
    _suit = suit;
    _position = position;
    _isFaceUp = true;
}
