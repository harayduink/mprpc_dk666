#pragma once
#include <unordered_map>
#include <string>
// 框架读取配置文件类
// 实际上是键值对的组合，让框架很方便的读取这些配置项

// rpcserviceip rpcserverport zookeeperip zookeeperport
class MprpcConfig
{
public:
    // 负责加载配置文件
    void LoadConfigFile(const char *config_file);
    // 查询配置项信息
    std::string Load(const std::string &key);
private:
    std::unordered_map<std::string, std::string> m_configMap;

    // 去掉字符串前后的空格和换行？
    void Trim(std::string &src_buf, char obj_c);
};