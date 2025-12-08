#include "StackView.h"
#include "configs/CardResConfig.h"
#include "configs/GameConfig.h"

bool StackView::init()
{
    if (!Node::init())
        return false;

    _topCard = nullptr;

    // Reserve Pile (Left side usually)
    _reservePile = cocos2d::Sprite::create(CardResConfig::getCardBackImagePath());
    if (_reservePile)
    {
        _reservePile->setScale(GameConstants::CARD_SCALE);
        _reservePile->setPosition(-150, 0);             // Offset from center
        _reservePile->setColor(cocos2d::Color3B::GRAY); // Distinguish
        this->addChild(_reservePile);

        auto listener = cocos2d::EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [this](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            cocos2d::Vec2 p = _reservePile->convertToNodeSpace(touch->getLocation());
            cocos2d::Size size = _reservePile->getContentSize();
            cocos2d::Rect r(0, 0, size.width, size.height);
            if (r.containsPoint(p))
            {
                return true;
            }
            return false;
        };
        listener->onTouchEnded = [this](cocos2d::Touch *touch, cocos2d::Event *event)
        {
            if (_reserveCallback)
            {
                _reserveCallback();
            }
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _reservePile);
    }

    return true;
}

void StackView::setTopCard(CardView *cardView)
{
    if (_topCard)
    {
        _topCard->removeFromParent();
    }
    _topCard = cardView;
    if (_topCard)
    {
        _topCard->setPosition(150, 0); // Right side
        this->addChild(_topCard);
    }
}

void StackView::setReserveCallback(const std::function<void()> &callback)
{
    _reserveCallback = callback;
}

void StackView::setReserveVisible(bool visible)
{
    if (_reservePile)
    {
        _reservePile->setVisible(visible);
    }
}
