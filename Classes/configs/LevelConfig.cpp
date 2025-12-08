#include "LevelConfig.h"
#include "json/document.h"

LevelConfig LevelConfigLoader::loadLevelConfig(const std::string &jsonContent)
{
    LevelConfig config;
    rapidjson::Document doc;
    doc.Parse(jsonContent.c_str());

    if (doc.HasParseError())
    {
        cocos2d::log("JSON Parse Error");
        return config;
    }

    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value &playfield = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfield.Size(); i++)
        {
            const rapidjson::Value &card = playfield[i];
            CardConfig cc;
            cc.face = (CardFaceType)card["CardFace"].GetInt();
            cc.suit = (CardSuitType)card["CardSuit"].GetInt();
            cc.position = cocos2d::Vec2(card["Position"]["x"].GetDouble(), card["Position"]["y"].GetDouble());
            config.playfieldCards.push_back(cc);
        }
    }

    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value &stack = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stack.Size(); i++)
        {
            const rapidjson::Value &card = stack[i];
            CardConfig cc;
            cc.face = (CardFaceType)card["CardFace"].GetInt();
            cc.suit = (CardSuitType)card["CardSuit"].GetInt();
            cc.position = cocos2d::Vec2(card["Position"]["x"].GetDouble(), card["Position"]["y"].GetDouble());
            config.stackCards.push_back(cc);
        }
    }

    return config;
}
