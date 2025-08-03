#pragma once

#include "mprpcconfig.h"
#include "mprpcchannel.h"
#include "mprpccontroller.h"



// MprpcApplication 类 - 设计为单例模式
class MprpcApplication {
public:
    // 1. 提供获取唯一实例的全局访问点
    // C++11 保证了函数内静态变量的初始化是线程安全的
    static MprpcApplication& GetInstance();
    // 外部获取配置项
    static MprpcConfig& GetConfig();
    // 在这里声明所有应用需要管理的公共方法
    // 例如：初始化、运行、获取配置等
    static void Init(int argc, char **argv);
    void Run();

private:
    // 2. 将构造函数私有化
    MprpcApplication(){} 
    
    // 3. 明确禁用拷贝构造和赋值操作符
    //    防止通过拷贝创建出多个实例
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication& operator=(const MprpcApplication&) = delete;
    static MprpcConfig m_config;
    // 在这里声明所有私有成员变量
    // 例如：配置文件对象、日志对象等
};