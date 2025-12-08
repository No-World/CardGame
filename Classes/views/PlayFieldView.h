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

    void addCard(CardView *cardView);
    void removeCard(int cardId);
    CardView *getCardView(int cardId);

private:
    std::map<int, CardView *> _cardViews;
};

#endif
