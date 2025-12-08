#ifndef __LANG_CONFIG_H__
#define __LANG_CONFIG_H__

#include "cocos2d.h"
#include <string>
#include <map>

class LangConfig
{
public:
    static LangConfig *getInstance();
    void loadLanguage(const std::string &langCode);
    std::string getString(const std::string &key);

private:
    LangConfig() {}
    static LangConfig *_instance;
    std::map<std::string, std::string> _strings;
};

#endif
