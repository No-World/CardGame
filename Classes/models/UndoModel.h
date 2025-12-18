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
    // 添加撤回操作
    void addAction(const UndoAction &action);
    // 是否有撤回操作
    bool hasActions() const;
    // 清空撤回操作
    void clear();
    // 弹出并返回最后一个撤回操作
    UndoAction popAction();
    // 查看最后一个撤回操作（不弹出）
    UndoAction peekAction() const;

private:
    std::vector<UndoAction> _actions;
};

#endif
