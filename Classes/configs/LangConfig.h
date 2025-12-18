#ifndef __LANG_CONFIG_H__
#define __LANG_CONFIG_H__

#include "cocos2d.h"
#include <string>
#include <map>

class LangConfig
{
public:
    // 获取单例实例
    static LangConfig *getInstance();
    // 加载语言配置
    void loadLanguage(const std::string &langCode);
    // 获取本地化字符串
    std::string getString(const std::string &key);

private:
    LangConfig() {}
    static LangConfig *_instance;
    std::map<std::string, std::string> _strings;
};

#endif
