#ifndef __STACK_VIEW_H__
#define __STACK_VIEW_H__

#include "cocos2d.h"
#include "CardView.h"

class StackView : public cocos2d::Node
{
public:
    CREATE_FUNC(StackView);
    bool init();

    void setTopCard(CardView *cardView);
    CardView *getTopCard() const { return _topCard; }

    void setReserveCallback(const std::function<void()> &callback);
    void setReserveVisible(bool visible);

private:
    CardView *_topCard;
    cocos2d::Sprite *_reservePile;
    std::function<void()> _reserveCallback;
};

#endif
