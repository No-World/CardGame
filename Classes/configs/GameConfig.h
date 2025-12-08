/*
 * @Author: NoWorld 2259881867@qq.com
 * @Date: 2025-12-08 22:18:35
 * @LastEditors: NoWorld 2259881867@qq.com
 * @LastEditTime: 2025-12-08 23:09:15
 * @FilePath: \CardGame\Classes\configs\GameConfig.h
 * @Description:
 */
#ifndef __GAME_CONFIG_H__
#define __GAME_CONFIG_H__

#include "cocos2d.h"

// 花色类型
enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,    // 梅花
    CST_DIAMONDS, // 方块
    CST_HEARTS,   // 红桃
    CST_SPADES,   // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};

// 正面类型
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

// 游戏常量
namespace GameConstants
{
    const float DESIGN_WIDTH = 1080.0f;
    const float DESIGN_HEIGHT = 2080.0f;

    // 区域尺寸
    const cocos2d::Size PLAYFIELD_SIZE(1080, 1500);
    const cocos2d::Size STACK_SIZE(1080, 580);

    // 卡牌缩放
    const float CARD_SCALE = 4.0f;
}

#endif // __GAME_CONFIG_H__
