#include "LangConfig.h"
#include "json/document.h"

LangConfig *LangConfig::_instance = nullptr;

LangConfig *LangConfig::getInstance()
{
    if (!_instance)
    {
        _instance = new LangConfig();
    }
    return _instance;
}

void LangConfig::loadLanguage(const std::string &langCode)
{
    std::string filename = "lang/" + langCode + ".json";
    std::string content = cocos2d::FileUtils::getInstance()->getStringFromFile(filename);

    if (content.empty())
    {
        cocos2d::log("Language file not found: %s", filename.c_str());
        return;
    }

    rapidjson::Document doc;
    doc.Parse(content.c_str());

    if (doc.HasParseError())
    {
        cocos2d::log("Language JSON parse error");
        return;
    }

    _strings.clear();
    for (auto &m : doc.GetObject())
    {
        if (m.value.IsString())
        {
            _strings[m.name.GetString()] = m.value.GetString();
        }
    }
}

std::string LangConfig::getString(const std::string &key)
{
    if (_strings.find(key) != _strings.end())
    {
        return _strings[key];
    }
    return key; // Return key if not found
}
