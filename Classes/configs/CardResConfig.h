#ifndef __CARD_RES_CONFIG_H__
#define __CARD_RES_CONFIG_H__

#include <string>
#include "configs/GameConfig.h"

class CardResConfig
{
public:
    static std::string getCardBackImagePath();
    static std::string getCardBackgroundPath();
    static std::string getGameBackgroundPath();
    static std::string getBigNumberPath(CardFaceType face, bool isRed);
    static std::string getSmallNumberPath(CardFaceType face, bool isRed);
    static std::string getSuitPath(CardSuitType suit);
};

#endif
