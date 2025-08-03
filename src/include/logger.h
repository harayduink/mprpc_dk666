#pragma once
#include "lockqueue.h"
// Mprpc框架提供的日志系统


enum LogLevel
{
    INFO, // 普通信息
    ERROR // 错误信息
};


class Logger
{
public:
    // 获取日志的单例
    static Logger & GetInstance();
    // 设置日志级别
    void SetLogLevel(LogLevel level);
    // 写日志
    void Log(std::string msg);
private:
    int m_logLevel; // 记录日志级别
    LockQueue<std::string> m_lockQue; // 日志缓冲队列

    Logger();
    Logger(const Logger&) = delete;
    Logger(Logger && ) = delete;
};


// 定义宏 尾部必须追加\符号
// LOG_INFO(%d,%f) 存在日志中，添加时刻信息
#define LOG_INFO(logmsgformat, ...) \
    do \
    { \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(INFO); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    }while(0);

#define LOG_ERR(logmsgformat, ...) \
    do \
    { \
        Logger &logger = Logger::GetInstance(); \
        logger.SetLogLevel(ERROR); \
        char c[1024] = {0}; \
        snprintf(c, 1024, logmsgformat, ##__VA_ARGS__); \
        logger.Log(c); \
    }while(0);