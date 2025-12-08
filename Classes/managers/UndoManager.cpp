#include "UndoManager.h"

UndoManager::UndoManager() : _undoModel(nullptr), _gameModel(nullptr)
{
    _undoModel = new UndoModel();
}

UndoManager::~UndoManager()
{
    if (_undoModel)
        delete _undoModel;
}

void UndoManager::init(GameModel *gameModel)
{
    _gameModel = gameModel;
}

void UndoManager::recordPlayfieldMove(int cardId, const cocos2d::Vec2 &originalPos)
{
    UndoAction action;
    action.type = UAT_PLAYFIELD_TO_STACK;
    action.cardId = cardId;
    action.originalPosition = originalPos;
    _undoModel->addAction(action);
}

void UndoManager::recordReserveMove(int cardId)
{
    UndoAction action;
    action.type = UAT_RESERVE_TO_STACK;
    action.cardId = cardId;
    _undoModel->addAction(action);
}

bool UndoManager::undo()
{
    if (!_undoModel || !_undoModel->hasActions() || !_gameModel)
        return false;

    UndoAction action = _undoModel->popAction();

    if (action.type == UAT_PLAYFIELD_TO_STACK)
    {
        _gameModel->restoreCardToPlayfield(action.cardId, action.originalPosition);
    }
    else if (action.type == UAT_RESERVE_TO_STACK)
    {
        _gameModel->undoDrawFromReserve();
        // Ensure the new top of stack is face up (if any)
        CardModel *newTop = _gameModel->getTopStackCard();
        if (newTop)
            newTop->setFaceUp(true);
    }

    return true;
}

bool UndoManager::hasActions() const
{
    return _undoModel && _undoModel->hasActions();
}

UndoAction UndoManager::peekAction() const
{
    if (!_undoModel)
        return {UAT_NONE, -1, cocos2d::Vec2::ZERO};
    return _undoModel->peekAction();
}
