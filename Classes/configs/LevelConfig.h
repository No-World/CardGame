#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include "cocos2d.h"
#include "configs/GameConfig.h"
#include <vector>
#include <string>

struct CardConfig
{
    CardFaceType face;
    CardSuitType suit;
    cocos2d::Vec2 position;
};

struct LevelConfig
{
    std::vector<CardConfig> playfieldCards;
    std::vector<CardConfig> stackCards;
};

class LevelConfigLoader
{
public:
    static LevelConfig loadLevelConfig(const std::string &jsonContent);
};

#endif
