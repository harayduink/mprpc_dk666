#include "mprpcconfig.h"
#include <iostream>
#include <string>

 // 去掉字符串前后的空格和换行？
void MprpcConfig::Trim(std::string &read_buf, char obj_c)
{
    int idx = read_buf.find_first_not_of(obj_c);
    if(idx != -1)
    {
        // 说明字符串前面有目标字符
        read_buf = read_buf.substr(idx, read_buf.size()-idx);

    }
    // 去掉字符串后面多余的目标字符 （找最后一个不是空格的）
    idx = read_buf.find_last_not_of(obj_c);
    if(idx != -1)
    {
        read_buf = read_buf.substr(0, idx+1);
    }
}

// 负责加载配置文件
void MprpcConfig::LoadConfigFile(const char *config_file)
{
    FILE *pf = fopen(config_file, "r");
    if(nullptr == pf)
    {
        std::cout << config_file << "is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 1.注释 2.正确的配置项（键值对） 3.去掉开头的多余空格
    while(!feof(pf))
    {
        char buf[512] = {0}; // 读取一行的用的缓存
        fgets(buf, 512, pf);

        // 去掉字符串前面多余的空格
        std::string read_buf(buf);
        Trim(read_buf, ' ');
        Trim(read_buf, '\n');
        if( read_buf.empty()||read_buf[0] == '#')
        {
            continue;
        }

        // 解析配置项
        int idx = read_buf.find('=');
        if(idx == -1)
        {
            // 配置不合法
            continue;
        }
        
        std::string key;
        std::string value;
        key = read_buf.substr(0, idx);
        Trim(key,' ');
        value = read_buf.substr(idx+1, read_buf.size()-idx);
        Trim(value,' ');
        Trim(value, '\n');
        m_configMap.insert({key, value});
        
    }
}

// 查询配置项信息
std::string MprpcConfig::Load(const std::string &key)
{
    auto it = m_configMap.find(key);
    if(it == m_configMap.end())
    {
        return "";
    }

    return it->second;
}