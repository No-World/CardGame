#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "cocos2d.h"
#include "models/CardModel.h"

class CardView : public cocos2d::Node
{
public:
    static CardView *create(CardModel *model);
    bool init(CardModel *model);

    void updateView();
    CardModel *getModel() const { return _model; }

    void setClickCallback(const std::function<void(int)> &callback);

private:
    CardModel *_model;
    cocos2d::Sprite *_bg;
    cocos2d::Sprite *_bigNum;
    cocos2d::Sprite *_smallNum;
    cocos2d::Sprite *_suit;

    std::function<void(int)> _clickCallback;

    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif
