#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include "models/UndoModel.h"
#include "models/GameModel.h"

class UndoManager
{
public:
    UndoManager();
    ~UndoManager();

    void init(GameModel *gameModel);
    void reset();

    void recordPlayfieldMove(int cardId, const cocos2d::Vec2 &originalPos);
    void recordReserveMove(int cardId);

    bool undo(); // Returns true if undo was successful
    bool hasActions() const;
    UndoAction peekAction() const;

private:
    UndoModel *_undoModel;
    GameModel *_gameModel; // Reference to GameModel to apply undo
};

#endif
