#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include "models/UndoModel.h"
#include "models/GameModel.h"

class UndoManager
{
public:
    UndoManager();
    ~UndoManager();

    // 初始化管理器
    void init(GameModel *gameModel);
    // 重置管理器
    void reset();

    // 记录桌面卡牌移动操作
    void recordPlayfieldMove(int cardId, const cocos2d::Vec2 &originalPos);
    // 记录备用牌堆移动操作
    void recordReserveMove(int cardId);

    // 执行撤回，成功返回true
    bool undo(); // Returns true if undo was successful
    // 是否有可撤回的操作
    bool hasActions() const;
    // 查看下一个撤回操作
    UndoAction peekAction() const;

private:
    UndoModel *_undoModel;
    GameModel *_gameModel; // Reference to GameModel to apply undo
};

#endif
