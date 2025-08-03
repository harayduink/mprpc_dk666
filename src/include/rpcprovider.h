#pragma once

#include "google/protobuf/service.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/TcpConnection.h>
#include <string>
#include <functional>
#include <google/protobuf/descriptor.h>
#include <unordered_map>
#include "logger.h"

// using muduo::net::TcpConnectionPtr;
// 框架提供的专门服务发布rpc服务的网络对象类
// 框架的运行类
class RpcProvider
{
public:
    // 这里是框架提供给外部使用的，可以发布rpc方法的接口调用。用service指向所有从这个类继承的对象
    void NotifyService(google::protobuf::Service *service);

    // 启动rpc服务节点，开始提供rpc远程网络调用服务
    void Run();
private:

    // 组合了tcpserver内置到了run方法中，作为局部变量，
    // std::unique_ptr<muduo::net::TcpServer> m_tcpserver;

    // service服务类型信息
    struct ServiceInfo
    {
        google::protobuf::Service *m_service; // 保存服务对象
        std::unordered_map<std::string, const google::protobuf::MethodDescriptor*> m_methodMap; // 保存服务方法

    };
    

    // 存储注册成功的服务对象和其方法的描述（抽象描述）
    std::unordered_map<std::string, ServiceInfo> m_serviceMap;

    

    // 组合了TcpServer 连接事件回调
    void OnConnection(const muduo::net::TcpConnectionPtr& conn);
    
    // 已建立连接用户的读写事件回调
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);
    muduo::net::EventLoop m_eventLoop;

    // Closure的回调操作，用于序列化rpc的响应和网络发送
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message* );



};