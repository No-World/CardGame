#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include "cocos2d.h"
#include <vector>

enum UndoActionType
{
    UAT_NONE,
    UAT_PLAYFIELD_TO_STACK,
    UAT_RESERVE_TO_STACK
};

struct UndoAction
{
    UndoActionType type;
    int cardId;
    cocos2d::Vec2 originalPosition; // For Playfield cards
};

/**
 * UndoModel
 * 运行时动态数据模型 - 回退数据
 */
class UndoModel
{
public:
    void addAction(const UndoAction &action);
    bool hasActions() const;
    UndoAction popAction();
    UndoAction peekAction() const;

private:
    std::vector<UndoAction> _actions;
};

#endif
