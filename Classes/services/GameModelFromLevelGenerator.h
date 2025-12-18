#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include "models/GameModel.h"
#include "configs/LevelConfig.h"

class GameModelFromLevelGenerator
{
public:
    // 根据关卡配置生成游戏模型
    static GameModel *generateGameModel(const LevelConfig &config);
};

#endif
