#ifndef __STACK_VIEW_H__
#define __STACK_VIEW_H__

#include "cocos2d.h"
#include "CardView.h"

class StackView : public cocos2d::Node
{
public:
    CREATE_FUNC(StackView);
    bool init();

    // 设置顶部卡牌
    void setTopCard(CardView *cardView);
    // 获取顶部卡牌
    CardView *getTopCard() const { return _topCard; }

    // 设置备用牌堆顶部卡牌
    void setReserveTopCard(CardView *cardView);
    // 获取备用牌堆顶部卡牌
    CardView *getReserveTopCard() const { return _reserveTopCard; }

    // 设置备用牌堆点击回调
    void setReserveCallback(const std::function<void()> &callback);
    // 设置备用牌堆可见性
    void setReserveVisible(bool visible);

private:
    CardView *_topCard;
    CardView *_reserveTopCard;
    cocos2d::Sprite *_reservePile;
    std::function<void()> _reserveCallback;
};

#endif
