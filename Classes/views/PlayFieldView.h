#ifndef __PLAY_FIELD_VIEW_H__
#define __PLAY_FIELD_VIEW_H__

#include "cocos2d.h"
#include "CardView.h"
#include <map>

class PlayFieldView : public cocos2d::Node
{
public:
    CREATE_FUNC(PlayFieldView);
    bool init();

    // 添加卡牌视图
    void addCard(CardView *cardView);
    // 移除卡牌视图
    void removeCard(int cardId);
    // 获取卡牌视图
    CardView *getCardView(int cardId);

private:
    std::map<int, CardView *> _cardViews;
};

#endif
