#include "StackView.h"
#include "configs/CardResConfig.h"
#include "configs/GameConfig.h"

bool StackView::init()
{
    if (!Node::init())
        return false;

    _topCard = nullptr;
    _reserveTopCard = nullptr;

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

void StackView::setReserveTopCard(CardView *cardView)
{
    if (_reserveTopCard)
    {
        _reserveTopCard->removeFromParent();
    }
    _reserveTopCard = cardView;
    if (_reserveTopCard)
    {
        _reserveTopCard->setPosition(-150, 0); // Left side (same as reserve pile)
        this->addChild(_reserveTopCard);
        
        // Forward click event to reserve callback
        _reserveTopCard->setClickCallback([this](int id){
            if (_reserveCallback) _reserveCallback();
        });
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
        // Only show reserve pile back if we don't have a face-up top card
        // But actually, if visible is false (empty), hide everything.
        // If visible is true, show _reservePile ONLY IF _reserveTopCard is null.
        
        if (!visible) {
            _reservePile->setVisible(false);
            if (_reserveTopCard) _reserveTopCard->setVisible(false);
        } else {
            if (_reserveTopCard) {
                _reservePile->setVisible(false); // Hide back, show card
                _reserveTopCard->setVisible(true);
            } else {
                _reservePile->setVisible(true); // Show back
            }
        }
    }
}
