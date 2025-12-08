#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "PlayFieldView.h"
#include "StackView.h"

class GameView : public cocos2d::Layer
{
public:
    static GameView *create();
    bool init();

    PlayFieldView *getPlayFieldView() const { return _playFieldView; }
    StackView *getStackView() const { return _stackView; }

    void setUndoCallback(const std::function<void()> &callback);
    void setReplayCallback(const std::function<void()> &callback);
    void setNextLevelCallback(const std::function<void()> &callback);
    void setCloseGameCallback(const std::function<void()> &callback);

    void showWinUI(bool hasNextLevel);
    void hideWinUI();
    void setStackViewVisible(bool visible);
    void setUndoButtonVisible(bool visible);

private:
    PlayFieldView *_playFieldView;
    StackView *_stackView;
    cocos2d::Menu *_undoMenu;
    cocos2d::Layer *_winLayer;

    std::function<void()> _undoCallback;
    std::function<void()> _replayCallback;
    std::function<void()> _nextLevelCallback;
    std::function<void()> _closeGameCallback;
};

#endif
