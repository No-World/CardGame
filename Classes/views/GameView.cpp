#include "GameView.h"
#include "configs/GameConfig.h"
#include "configs/CardResConfig.h"
#include "configs/LangConfig.h"

GameView *GameView::create()
{
    GameView *ret = new (std::nothrow) GameView();
    if (ret && ret->init())
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool GameView::init()
{
    if (!Layer::init())
        return false;

    // Background
    auto bg = cocos2d::Sprite::create(CardResConfig::getGameBackgroundPath());
    if (bg)
    {
        bg->setPosition(GameConstants::DESIGN_WIDTH / 2, GameConstants::DESIGN_HEIGHT / 2);
        // Scale to cover
        float scaleX = GameConstants::DESIGN_WIDTH / bg->getContentSize().width;
        float scaleY = GameConstants::DESIGN_HEIGHT / bg->getContentSize().height;
        bg->setScale(std::max(scaleX, scaleY));
        this->addChild(bg);
    }

    // PlayField
    _playFieldView = PlayFieldView::create();
    // Shift PlayField up to make it "Top" aligned
    // Original cards are around y=600~1000. Screen height is 2080.
    // We want them near the top. Let's shift by +700.
    _playFieldView->setPosition(0, 700);
    this->addChild(_playFieldView);

    // StackView
    _stackView = StackView::create();
    _stackView->setPosition(GameConstants::DESIGN_WIDTH / 2, 290);
    this->addChild(_stackView);

    // Undo Button
    auto undoLabel = cocos2d::Label::createWithSystemFont(LangConfig::getInstance()->getString("undo"), "Arial", 48);
    undoLabel->setColor(cocos2d::Color3B::RED); // Make it visible
    auto undoItem = cocos2d::MenuItemLabel::create(undoLabel, [this](cocos2d::Ref *sender)
                                                   {
        if (_undoCallback) _undoCallback(); });
    undoItem->setPosition(GameConstants::DESIGN_WIDTH - 150, 150); // Move it a bit

    _undoMenu = cocos2d::Menu::create(undoItem, nullptr);
    _undoMenu->setPosition(0, 0);
    this->addChild(_undoMenu, 1000); // High Z-order

    _winLayer = nullptr;

    return true;
}

void GameView::setUndoCallback(const std::function<void()> &callback)
{
    _undoCallback = callback;
}

void GameView::setReplayCallback(const std::function<void()> &callback)
{
    _replayCallback = callback;
}

void GameView::setNextLevelCallback(const std::function<void()> &callback)
{
    _nextLevelCallback = callback;
}

void GameView::setCloseGameCallback(const std::function<void()> &callback)
{
    _closeGameCallback = callback;
}

void GameView::setStackViewVisible(bool visible)
{
    if (_stackView)
        _stackView->setVisible(visible);
}

void GameView::setUndoButtonVisible(bool visible)
{
    if (_undoMenu)
        _undoMenu->setVisible(visible);
}

void GameView::showWinUI(bool hasNextLevel)
{
    if (_winLayer)
    {
        _winLayer->removeFromParent();
    }

    _winLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
    this->addChild(_winLayer, 2000);

    auto winLabel = cocos2d::Label::createWithSystemFont(LangConfig::getInstance()->getString("win_title"), "Arial", 96);
    winLabel->setPosition(GameConstants::DESIGN_WIDTH / 2, GameConstants::DESIGN_HEIGHT / 2 + 200);
    _winLayer->addChild(winLabel);

    auto replayLabel = cocos2d::Label::createWithSystemFont(LangConfig::getInstance()->getString("replay"), "Arial", 64);
    auto replayItem = cocos2d::MenuItemLabel::create(replayLabel, [this](cocos2d::Ref *sender)
                                                     {
        if (_replayCallback) _replayCallback(); });
    replayItem->setPosition(GameConstants::DESIGN_WIDTH / 2, GameConstants::DESIGN_HEIGHT / 2);

    cocos2d::MenuItemLabel *nextItem = nullptr;
    if (hasNextLevel)
    {
        auto nextLabel = cocos2d::Label::createWithSystemFont(LangConfig::getInstance()->getString("next_level"), "Arial", 64);
        nextItem = cocos2d::MenuItemLabel::create(nextLabel, [this](cocos2d::Ref *sender)
                                                  {
            if (_nextLevelCallback) _nextLevelCallback(); });
        nextItem->setPosition(GameConstants::DESIGN_WIDTH / 2, GameConstants::DESIGN_HEIGHT / 2 - 150);
    }
    else
    {
        auto allClearLabel = cocos2d::Label::createWithSystemFont(LangConfig::getInstance()->getString("all_cleared"), "Arial", 48);
        allClearLabel->setPosition(GameConstants::DESIGN_WIDTH / 2, GameConstants::DESIGN_HEIGHT / 2 - 150);
        _winLayer->addChild(allClearLabel);
    }

    auto closeLabel = cocos2d::Label::createWithSystemFont(LangConfig::getInstance()->getString("close_game"), "Arial", 64);
    auto closeItem = cocos2d::MenuItemLabel::create(closeLabel, [this](cocos2d::Ref *sender)
                                                    {
        if (_closeGameCallback) _closeGameCallback(); });
    closeItem->setPosition(GameConstants::DESIGN_WIDTH / 2, GameConstants::DESIGN_HEIGHT / 2 - 300);

    auto menu = cocos2d::Menu::create(replayItem, closeItem, nullptr);
    if (nextItem)
    {
        menu->addChild(nextItem);
    }
    menu->setPosition(0, 0);
    _winLayer->addChild(menu);
}

void GameView::hideWinUI()
{
    if (_winLayer)
    {
        _winLayer->removeFromParent();
        _winLayer = nullptr;
    }
}
