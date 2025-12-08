#include "CardView.h"
#include "configs/CardResConfig.h"

CardView *CardView::create(CardModel *model)
{
    CardView *ret = new (std::nothrow) CardView();
    if (ret && ret->init(model))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init(CardModel *model)
{
    if (!Node::init())
        return false;

    _model = model;
    _bigNum = nullptr;
    _smallNum = nullptr;
    _suit = nullptr;

    // Create sprites
    _bg = cocos2d::Sprite::create(CardResConfig::getCardBackgroundPath());
    if (_bg)
    {
        this->addChild(_bg);
        this->setContentSize(_bg->getContentSize()); // Set Node size to match bg
    }

    this->setScale(GameConstants::CARD_SCALE);

    // Setup touch listener
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](cocos2d::Touch *touch, cocos2d::Event *event)
    {
        if (!_bg)
            return false;

        cocos2d::Vec2 p = _bg->convertToNodeSpace(touch->getLocation());
        cocos2d::Size size = _bg->getContentSize();
        cocos2d::Rect r(0, 0, size.width, size.height);
        if (r.containsPoint(p))
        {
            return true;
        }
        return false;
    };
    listener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    updateView();

    return true;
}

void CardView::updateView()
{
    if (!_model || !_bg)
        return;

    // Clear old sprites if any (except bg)
    if (_bigNum)
    {
        _bigNum->removeFromParent();
        _bigNum = nullptr;
    }
    if (_smallNum)
    {
        _smallNum->removeFromParent();
        _smallNum = nullptr;
    }
    if (_suit)
    {
        _suit->removeFromParent();
        _suit = nullptr;
    }

    if (_model->isFaceUp())
    {
        bool isRed = (_model->getSuit() == CST_DIAMONDS || _model->getSuit() == CST_HEARTS);

        std::string bigNumPath = CardResConfig::getBigNumberPath(_model->getFace(), isRed);
        _bigNum = cocos2d::Sprite::create(bigNumPath);
        if (_bigNum)
        {
            _bigNum->setPosition(0, 0); // Center
            this->addChild(_bigNum);
        }

        std::string smallNumPath = CardResConfig::getSmallNumberPath(_model->getFace(), isRed);
        _smallNum = cocos2d::Sprite::create(smallNumPath);
        if (_smallNum)
        {
            // Adjust position based on bg size
            float x = -_bg->getContentSize().width + 30;
            float y = _bg->getContentSize().height / 2 - 10;
            _smallNum->setPosition(x, y);
            this->addChild(_smallNum);
        }

        std::string suitPath = CardResConfig::getSuitPath(_model->getSuit());
        _suit = cocos2d::Sprite::create(suitPath);
        if (_suit)
        {
            float x = _bg->getContentSize().width - 30;
            float y = _bg->getContentSize().height / 2 - 10;
            _suit->setPosition(x, y);
            this->addChild(_suit);
        }

        _bg->setColor(cocos2d::Color3B::WHITE);
    }
    else
    {
        // Face down
        _bg->setColor(cocos2d::Color3B::GRAY); // Simple representation
    }
}

void CardView::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (_clickCallback)
    {
        _clickCallback(_model->getId());
    }
}

void CardView::setClickCallback(const std::function<void(int)> &callback)
{
    _clickCallback = callback;
}
