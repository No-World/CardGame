#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__

#include <string>
#include "configs/GameConfig.h"

class CardResConfig
{
public:
    // 获取卡背图片路径
    static std::string getCardBackImagePath();
    // 获取卡牌背景图片路径
    static std::string getCardBackgroundPath();
    // 获取游戏背景图片路径
    static std::string getGameBackgroundPath();
    // 获取大数字图片路径
    static std::string getBigNumberPath(CardFaceType face, bool isRed);
    // 获取小数字图片路径
    static std::string getSmallNumberPath(CardFaceType face, bool isRed);
    // 获取花色图片路径
    static std::string getSuitPath(CardSuitType suit);
};

#endif
