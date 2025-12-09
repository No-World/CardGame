#include "GameController.h"
#include "configs/LevelConfig.h"
#include "services/GameModelFromLevelGenerator.h"
#include <cmath>

GameController::GameController()
    : _gameModel(nullptr), _gameView(nullptr), _undoManager(nullptr), _currentLevelId(1)
{
    _undoManager = new UndoManager();
}

GameController::~GameController()
{
    if (_gameModel)
        delete _gameModel;
    if (_undoManager)
        delete _undoManager;
}

void GameController::init(cocos2d::Scene *scene)
{
    _gameView = GameView::create();
    scene->addChild(_gameView);

    _gameView->setUndoCallback([this]()
                               { this->onUndoClicked(); });

    _gameView->getStackView()->setReserveCallback([this]()
                                                  { this->onReserveClicked(); });

    _gameView->setReplayCallback([this]()
                                 { this->onReplayClicked(); });
    _gameView->setNextLevelCallback([this]()
                                    { this->onNextLevelClicked(); });
    _gameView->setCloseGameCallback([this]()
                                    { this->onCloseGameClicked(); });
}

void GameController::startGame(int levelId)
{
    _currentLevelId = levelId;
    _gameView->hideWinUI();
    _gameView->setStackViewVisible(true);
    _gameView->setUndoButtonVisible(true);

    // Debug: Print Search Paths
    auto fileUtils = cocos2d::FileUtils::getInstance();
    std::vector<std::string> searchPaths = fileUtils->getSearchPaths();
    cocos2d::log("Current Search Paths:");
    for (const auto &path : searchPaths)
    {
        cocos2d::log("  %s", path.c_str());
    }

    // Load config
    std::string filename = "levels/level" + std::to_string(levelId) + ".json";
    std::string fullPath = fileUtils->fullPathForFilename(filename);
    cocos2d::log("Target Level File: %s", filename.c_str());
    cocos2d::log("Resolved Full Path: %s", fullPath.c_str());

    std::string jsonContent = fileUtils->getStringFromFile(filename);
    cocos2d::log("JSON Content Length: %d", (int)jsonContent.length());
    if (jsonContent.length() > 0)
    {
        cocos2d::log("JSON Content Preview: %s", jsonContent.substr(0, 200).c_str());
    }
    else
    {
        cocos2d::log("ERROR: JSON Content is empty! File might not exist or path is wrong.");
    }

    LevelConfig config = LevelConfigLoader::loadLevelConfig(jsonContent);

    cocos2d::log("Level Config Loaded:");
    cocos2d::log("  Playfield Cards: %d", (int)config.playfieldCards.size());
    cocos2d::log("  Stack Cards: %d", (int)config.stackCards.size());

    // Generate model
    if (_gameModel)
        delete _gameModel;
    _gameModel = GameModelFromLevelGenerator::generateGameModel(config);

    // Reset all playfield cards to Face Down initially
    // This ensures that only the top-most cards are revealed by updateFaceUpState
    for (auto card : _gameModel->getPlayfieldCards())
    {
        card->setFaceUp(false);
    }

    // Ensure top stack card is Face Up
    CardModel *topStack = _gameModel->getTopStackCard();
    if (topStack)
    {
        topStack->setFaceUp(true);
    }

    // Ensure all reserve cards are Face Down initially
    for (auto card : _gameModel->getReserveCards())
    {
        card->setFaceUp(false);
    }

    // Init UndoManager
    _undoManager->init(_gameModel);

    updateFaceUpState();
    updateView();
}
void GameController::updateView()
{
    if (!_gameModel || !_gameView)
        return;

    // Update Playfield
    auto playFieldView = _gameView->getPlayFieldView();
    const auto &playfieldCards = _gameModel->getPlayfieldCards();

    for (auto card : playfieldCards)
    {
        if (!playFieldView->getCardView(card->getId()))
        {
            CardView *cv = CardView::create(card);
            cv->setPosition(card->getPosition());
            cv->setClickCallback([this](int id)
                                 { this->onCardClicked(id); });
            playFieldView->addCard(cv);
        }
        else
        {
            CardView *cv = playFieldView->getCardView(card->getId());
            cv->setPosition(card->getPosition());
            cv->updateView();
        }
    }

    // Update Stack
    auto stackView = _gameView->getStackView();
    CardModel *topStack = _gameModel->getTopStackCard();
    if (topStack)
    {
        CardView *currentTopView = stackView->getTopCard();
        if (!currentTopView || currentTopView->getModel()->getId() != topStack->getId())
        {
            CardView *cv = CardView::create(topStack);
            stackView->setTopCard(cv);
        }
    }
    else
    {
        stackView->setTopCard(nullptr);
    }

    // Update Reserve Pile
    // Check if top reserve card is face up
    CardModel *topReserve = _gameModel->getTopReserveCard();
    if (topReserve && topReserve->isFaceUp())
    {
        CardView *currentReserveView = stackView->getReserveTopCard();
        if (!currentReserveView || currentReserveView->getModel()->getId() != topReserve->getId())
        {
            CardView *cv = CardView::create(topReserve);
            stackView->setReserveTopCard(cv);
        }
    }
    else
    {
        stackView->setReserveTopCard(nullptr);
    }

    // Update Reserve Pile Visibility
    bool hasReserve = !_gameModel->getReserveCards().empty();
    stackView->setReserveVisible(hasReserve);

    checkWinCondition();
}

void GameController::checkWinCondition()
{
    if (!_gameModel)
        return;

    if (_gameModel->getPlayfieldCards().empty())
    {
        // Win!
        _gameView->setStackViewVisible(false);
        _gameView->setUndoButtonVisible(false);

        // Check next level
        std::string nextLevelFile = "levels/level" + std::to_string(_currentLevelId + 1) + ".json";
        bool hasNext = cocos2d::FileUtils::getInstance()->isFileExist(nextLevelFile);

        // Also check if we can resolve it (just to be safe with search paths)
        if (!hasNext)
        {
            std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(nextLevelFile);
            if (!fullPath.empty())
                hasNext = true;
        }

        _gameView->showWinUI(hasNext);
    }
}

void GameController::onReplayClicked()
{
    startGame(_currentLevelId);
}

void GameController::onNextLevelClicked()
{
    startGame(_currentLevelId + 1);
}

void GameController::onCloseGameClicked()
{
    cocos2d::Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameController::onCardClicked(int cardId)
{
    CardModel *card = _gameModel->getCardById(cardId);
    if (!card)
        return;

    if (!card->isFaceUp())
        return;

    // Check if covered by any other playfield card (even if face up)
    // Card size based on actual resource size (182x282)
    cocos2d::Size cardSize(182 * GameConstants::CARD_SCALE, 282 * GameConstants::CARD_SCALE);
    cocos2d::Size hitBoxSize = cardSize * 0.5f;

    bool isPlayfield = false;
    const auto &cards = _gameModel->getPlayfieldCards();
    
    // Find index of current card
    int cardIndex = -1;
    for (size_t i = 0; i < cards.size(); ++i) {
        if (cards[i]->getId() == cardId) {
            cardIndex = i;
            isPlayfield = true;
            break;
        }
    }

    if (!isPlayfield)
        return;

    // Check coverage
    cocos2d::Rect currentRect(card->getPosition().x - hitBoxSize.width / 2,
                              card->getPosition().y - hitBoxSize.height / 2,
                              hitBoxSize.width, hitBoxSize.height);

    for (size_t j = cardIndex + 1; j < cards.size(); ++j)
    {
        CardModel *other = cards[j];
        cocos2d::Rect otherRect(other->getPosition().x - hitBoxSize.width / 2,
                                other->getPosition().y - hitBoxSize.height / 2,
                                hitBoxSize.width, hitBoxSize.height);
        if (currentRect.intersectsRect(otherRect))
        {
            // Covered, cannot click
            return;
        }
    }

    CardModel *topStack = _gameModel->getTopStackCard();
    if (!topStack)
        return;

    if (canMatch(card, topStack))
    {
        _undoManager->recordPlayfieldMove(cardId, card->getPosition());
        _gameModel->moveCardToStack(cardId);

        auto playFieldView = _gameView->getPlayFieldView();
        CardView *cv = playFieldView->getCardView(cardId);
        if (cv)
        {
            cocos2d::Vec2 targetPos = _gameView->getStackView()->convertToWorldSpace(cocos2d::Vec2(150, 0));
            cocos2d::Vec2 targetPosLocal = playFieldView->convertToNodeSpace(targetPos);

            cv->setLocalZOrder(100);
            auto move = cocos2d::MoveTo::create(0.5f, targetPosLocal);
            auto callback = cocos2d::CallFunc::create([this, cardId]()
                                                      {
                auto pfv = _gameView->getPlayFieldView();
                pfv->removeCard(cardId);
                this->updateFaceUpState();
                this->updateView(); });
            cv->runAction(cocos2d::Sequence::create(move, callback, nullptr));
        }
        else
        {
            updateView();
        }
    }
}

void GameController::onReserveClicked()
{
    CardModel *newTop = _gameModel->drawFromReserve();
    if (newTop)
    {
        newTop->setFaceUp(true);
        _undoManager->recordReserveMove(newTop->getId());
        updateView();
    }
}

void GameController::onUndoClicked()
{
    if (!_undoManager->hasActions())
        return;

    UndoAction action = _undoManager->peekAction();

    // Prepare animation data
    CardModel *cardModel = _gameModel->getCardById(action.cardId);
    if (!cardModel)
        return;

    // Create flying card (Visual representation)
    // We create it before undoing so it reflects the state on the stack (Face Up)
    auto flyingCard = CardView::create(cardModel);
    if (!flyingCard)
        return;

    // Set initial position (from Stack)
    auto stackView = _gameView->getStackView();
    auto topCard = stackView->getTopCard();

    cocos2d::Vec2 startPosWorld;
    if (topCard)
    {
        startPosWorld = topCard->getParent()->convertToWorldSpace(topCard->getPosition());
    }
    else
    {
        // Fallback if stack is empty
        startPosWorld = stackView->convertToWorldSpace(cocos2d::Vec2(150, 0));
    }

    flyingCard->setPosition(_gameView->convertToNodeSpace(startPosWorld));
    flyingCard->setCascadeOpacityEnabled(true);
    _gameView->addChild(flyingCard, 1000); // High Z-order

    // Perform Undo Logic
    if (_undoManager->undo())
    {
        updateFaceUpState();
        updateView();

        // Now find the destination and animate
        cocos2d::Vec2 targetPosWorld;
        CardView *targetCardView = nullptr;

        if (action.type == UAT_PLAYFIELD_TO_STACK)
        {
            auto pfView = _gameView->getPlayFieldView();
            targetCardView = pfView->getCardView(action.cardId);
            if (targetCardView)
            {
                targetPosWorld = targetCardView->getParent()->convertToWorldSpace(targetCardView->getPosition());
            }
        }
        else if (action.type == UAT_RESERVE_TO_STACK)
        {
            // Target is reserve pile
            targetPosWorld = stackView->convertToWorldSpace(cocos2d::Vec2(-150, 0));
        }

        // Hide target card if it exists so we can fly into its place
        if (targetCardView)
        {
            targetCardView->setCascadeOpacityEnabled(true);
            targetCardView->setOpacity(0);
        }

        // Animate
        cocos2d::Vec2 targetPosLocal = _gameView->convertToNodeSpace(targetPosWorld);
        auto move = cocos2d::MoveTo::create(0.3f, targetPosLocal);
        auto callback = cocos2d::CallFunc::create([flyingCard, targetCardView]()
                                                  {
            flyingCard->removeFromParent();
            if (targetCardView) {
                targetCardView->setOpacity(255);
            } });

        flyingCard->runAction(cocos2d::Sequence::create(move, callback, nullptr));
    }
    else
    {
        // Undo failed, cleanup
        flyingCard->removeFromParent();
    }
}

bool GameController::canMatch(CardModel *card, CardModel *target)
{
    if (!card || !target)
        return false;

    int face1 = (int)card->getFace();
    int face2 = (int)target->getFace();

    int diff = std::abs(face1 - face2);
    if (diff == 1)
        return true;
    if (diff == 12)
        return true; // A and K

    return false;
}

void GameController::updateFaceUpState()
{
    // Card size based on actual resource size (182x282)
    cocos2d::Size cardSize(182 * GameConstants::CARD_SCALE, 282 * GameConstants::CARD_SCALE);
    // Shrink the hit box slightly to avoid edge cases
    cocos2d::Size hitBoxSize = cardSize * 0.5f;

    const auto &cards = _gameModel->getPlayfieldCards();

    for (size_t i = 0; i < cards.size(); ++i)
    {
        CardModel *current = cards[i];
        bool covered = false;
        cocos2d::Rect currentRect(current->getPosition().x - hitBoxSize.width / 2,
                                  current->getPosition().y - hitBoxSize.height / 2,
                                  hitBoxSize.width, hitBoxSize.height);

        for (size_t j = i + 1; j < cards.size(); ++j)
        {
            CardModel *other = cards[j];
            cocos2d::Rect otherRect(other->getPosition().x - hitBoxSize.width / 2,
                                    other->getPosition().y - hitBoxSize.height / 2,
                                    hitBoxSize.width, hitBoxSize.height);
            if (currentRect.intersectsRect(otherRect))
            {
                covered = true;
                break;
            }
        }
        
        // Only flip face up if not covered.
        // If covered, we keep the current state (so if it was already face up, it stays face up).
        if (!covered) {
            current->setFaceUp(true);
        }
    }
}
