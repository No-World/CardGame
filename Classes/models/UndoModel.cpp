#include "UndoModel.h"

void UndoModel::addAction(const UndoAction &action)
{
    _actions.push_back(action);
}

bool UndoModel::hasActions() const
{
    return !_actions.empty();
}

void UndoModel::clear()
{
    _actions.clear();
}

UndoAction UndoModel::popAction()
{
    if (_actions.empty())
    {
        // Should check hasActions before calling
        return {UAT_NONE, -1, cocos2d::Vec2::ZERO};
    }
    UndoAction action = _actions.back();
    _actions.pop_back();
    return action;
}

UndoAction UndoModel::peekAction() const
{
    if (_actions.empty())
    {
        return {UAT_NONE, -1, cocos2d::Vec2::ZERO};
    }
    return _actions.back();
}
