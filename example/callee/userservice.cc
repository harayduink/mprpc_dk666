#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"

/*
UserService原来是一个本地服务，提供了两个进程内的本地方法，Login和GetFriendLists
*/

class UserService: public fixbug::UserServiceRpc// 使用在rpc服务发布端
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login" << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;
        return false;
    }

    bool Register(uint32_t id, std::string name, std::string pwd)
    {
        std::cout << "doing local service: Register" << std::endl;
        std::cout << "id:" << id << "name:" << name << " pwd:" << pwd << std::endl;
        return true;
    }

    /*
    重写基类UserServiceRpc的虚函数，下面这些方法都是框架直接调用
    1. caller ==>  Login(LoginRequest) ==>muduo ==> callee
    2. callee ==>  Login(LoinRequest) ==> 交到下面重写的Login方法上
    */
    void Login(::google::protobuf::RpcController* controller,
                       const ::fixbug::LoginRequest* request,
                       ::fixbug::LoginResponse* response,
                       ::google::protobuf::Closure* done)
    {
        // 框架给业务上报了请求参数LoginRequest，应用获取相应的数据做本地业务
        std::string name = request->name();
        std::string pwd = request->pwd();


        bool login_result = Login(name, pwd); // 做本地业务

        // 把响应写入response,包括错误码，错误消息，返回值
        fixbug::ResultCode *code = response->mutable_result();
        code->set_errcode(1);
        code->set_errmsg("Login do Error!");
        response->set_success(login_result);
        
        // 执行回调操作 执行响应对象数据的序列化和网络发送
        done->Run();
    }


    void Register(google::protobuf::RpcController* controller,
                       const ::fixbug::RegisterRequest* request,
                       ::fixbug::RegisterResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t id = request->id();
        std::string name = request->name();
        std::string pwd = request->pwd();
        
        bool ret = Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();
    }

      
};

//zookeeper服务器端口号

int main(int argc, char** argv)
{
    // 调用框架的初始化操作
    MprpcApplication::GetInstance().Init(argc, argv);

    // 吧UserService对象发布到rpc节点上
    // provider是一个网络服务对象
    RpcProvider provider;
    provider.NotifyService(new UserService());
    // 通过NotifyService发布服务节点

    // 启动一个rpc服务节点，Run以后，进程进入阻塞状态
    provider.Run();
    return 0;
}