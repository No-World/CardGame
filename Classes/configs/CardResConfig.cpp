#include "CardResConfig.h"

std::string CardResConfig::getCardBackImagePath()
{
    return "res/card_general.png"; // Placeholder, maybe tint it in view
}

std::string CardResConfig::getCardBackgroundPath()
{
    return "res/card_general.png";
}

std::string CardResConfig::getGameBackgroundPath()
{
    return "res/background.png";
}

std::string CardResConfig::getBigNumberPath(CardFaceType face, bool isRed)
{
    std::string color = isRed ? "red" : "black";
    std::string faceStr;
    switch (face)
    {
    case CFT_ACE:
        faceStr = "A";
        break;
    case CFT_TWO:
        faceStr = "2";
        break;
    case CFT_THREE:
        faceStr = "3";
        break;
    case CFT_FOUR:
        faceStr = "4";
        break;
    case CFT_FIVE:
        faceStr = "5";
        break;
    case CFT_SIX:
        faceStr = "6";
        break;
    case CFT_SEVEN:
        faceStr = "7";
        break;
    case CFT_EIGHT:
        faceStr = "8";
        break;
    case CFT_NINE:
        faceStr = "9";
        break;
    case CFT_TEN:
        faceStr = "10";
        break;
    case CFT_JACK:
        faceStr = "J";
        break;
    case CFT_QUEEN:
        faceStr = "Q";
        break;
    case CFT_KING:
        faceStr = "K";
        break;
    default:
        faceStr = "A";
        break;
    }
    return "res/number/big_" + color + "_" + faceStr + ".png";
}

std::string CardResConfig::getSmallNumberPath(CardFaceType face, bool isRed)
{
    std::string color = isRed ? "red" : "black";
    std::string faceStr;
    switch (face)
    {
    case CFT_ACE:
        faceStr = "A";
        break;
    case CFT_TWO:
        faceStr = "2";
        break;
    case CFT_THREE:
        faceStr = "3";
        break;
    case CFT_FOUR:
        faceStr = "4";
        break;
    case CFT_FIVE:
        faceStr = "5";
        break;
    case CFT_SIX:
        faceStr = "6";
        break;
    case CFT_SEVEN:
        faceStr = "7";
        break;
    case CFT_EIGHT:
        faceStr = "8";
        break;
    case CFT_NINE:
        faceStr = "9";
        break;
    case CFT_TEN:
        faceStr = "10";
        break;
    case CFT_JACK:
        faceStr = "J";
        break;
    case CFT_QUEEN:
        faceStr = "Q";
        break;
    case CFT_KING:
        faceStr = "K";
        break;
    default:
        faceStr = "A";
        break;
    }
    return "res/number/small_" + color + "_" + faceStr + ".png";
}

std::string CardResConfig::getSuitPath(CardSuitType suit)
{
    switch (suit)
    {
    case CST_CLUBS:
        return "res/suits/club.png";
    case CST_DIAMONDS:
        return "res/suits/diamond.png";
    case CST_HEARTS:
        return "res/suits/heart.png";
    case CST_SPADES:
        return "res/suits/spade.png";
    default:
        return "";
    }
}
