#include "GameModel.h"

GameModel::GameModel()
{
}

GameModel::~GameModel()
{
    for (auto card : _playfieldCards)
        delete card;
    _playfieldCards.clear();

    for (auto card : _stackCards)
        delete card;
    _stackCards.clear();

    for (auto card : _reserveCards)
        delete card;
    _reserveCards.clear();
}

void GameModel::addPlayfieldCard(CardModel *card)
{
    _playfieldCards.push_back(card);
}

void GameModel::addStackCard(CardModel *card)
{
    _stackCards.push_back(card);
}

void GameModel::addReserveCard(CardModel *card)
{
    _reserveCards.push_back(card);
}

CardModel *GameModel::getCardById(int id)
{
    for (auto card : _playfieldCards)
        if (card->getId() == id)
            return card;
    for (auto card : _stackCards)
        if (card->getId() == id)
            return card;
    for (auto card : _reserveCards)
        if (card->getId() == id)
            return card;
    return nullptr;
}

void GameModel::moveCardToStack(int cardId)
{
    for (auto it = _playfieldCards.begin(); it != _playfieldCards.end(); ++it)
    {
        if ((*it)->getId() == cardId)
        {
            CardModel *card = *it;
            _playfieldCards.erase(it);
            _stackCards.push_back(card);
            break;
        }
    }
}

CardModel *GameModel::drawFromReserve()
{
    if (_reserveCards.empty())
        return nullptr;
    CardModel *card = _reserveCards.back();
    _reserveCards.pop_back();
    _stackCards.push_back(card);
    return card;
}

CardModel *GameModel::getTopStackCard()
{
    if (_stackCards.empty())
        return nullptr;
    return _stackCards.back();
}

void GameModel::restoreCardToPlayfield(int cardId, const cocos2d::Vec2 &pos)
{
    if (_stackCards.empty())
        return;

    CardModel *card = _stackCards.back();
    if (card->getId() == cardId)
    {
        _stackCards.pop_back();
        card->setPosition(pos);
        _playfieldCards.push_back(card);
    }
}

void GameModel::undoDrawFromReserve()
{
    if (_stackCards.empty())
        return;
    CardModel *card = _stackCards.back();
    _stackCards.pop_back();
    _reserveCards.push_back(card);
}
