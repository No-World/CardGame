#include "PlayFieldView.h"

bool PlayFieldView::init()
{
    if (!Node::init())
        return false;
    return true;
}

void PlayFieldView::addCard(CardView *cardView)
{
    if (!cardView)
        return;
    this->addChild(cardView);
    _cardViews[cardView->getModel()->getId()] = cardView;
}

void PlayFieldView::removeCard(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end())
    {
        it->second->removeFromParent();
        _cardViews.erase(it);
    }
}

CardView *PlayFieldView::getCardView(int cardId)
{
    auto it = _cardViews.find(cardId);
    if (it != _cardViews.end())
    {
        return it->second;
    }
    return nullptr;
}
