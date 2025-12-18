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

    // 获取桌面视图
    PlayFieldView *getPlayFieldView() const { return _playFieldView; }
    // 获取堆叠视图
    StackView *getStackView() const { return _stackView; }

    // 设置撤回回调
    void setUndoCallback(const std::function<void()> &callback);
    // 设置重玩回调
    void setReplayCallback(const std::function<void()> &callback);
    // 设置下一关回调
    void setNextLevelCallback(const std::function<void()> &callback);
    // 设置关闭游戏回调
    void setCloseGameCallback(const std::function<void()> &callback);

    // 显示胜利界面
    void showWinUI(bool hasNextLevel);
    // 隐藏胜利界面
    void hideWinUI();
    // 设置堆叠视图可见性
    void setStackViewVisible(bool visible);
    // 设置撤回按钮可见性
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
