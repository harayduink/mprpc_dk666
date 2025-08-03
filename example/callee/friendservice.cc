#include <iostream>
#include <string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <vector>
#include "logger.h"

class FriendService: public  fixbug::FriendServiceRpc
{
public:
    std::vector <std::string> GetFriendsList(uint32_t userid)
    {
        std::cout << "do GetFriendsList service!"  << "userid: " << userid << std::endl;
        std::vector<std::string> vec;
        vec.push_back("gao yang");
        vec.push_back("li si");
        vec.push_back("wang wu");

        return vec;
    }

    void GetFriendsList(google::protobuf::RpcController* controller,
                       const ::fixbug::GetFriendRequest* request,
                       ::fixbug::GetFriendResponse* response,
                       ::google::protobuf::Closure* done)
    {
        uint32_t userid = request->userid();

        std::vector<std::string> friendsList = GetFriendsList(userid);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        for(std::string &name:friendsList)
        {
            std::string *p = response->add_friends(); // 对于protobuf中的列表数据添加新元素的流程，第一个
            *p = name;
        }
        for(int i = 0; i<response->friends_size(); i++)
        {
            std::cout << "id:" << i << " name:" << response->friends(i) << std::endl;
        }
        done->Run();
    }
};



int main(int argc, char** argv)
{
    LOG_INFO("first log message!");
    LOG_INFO("%s:%s:%d", __FILE__, __FUNCTION__, __LINE__);
    
    // 调用框架的初始化操作
    MprpcApplication::GetInstance().Init(argc, argv);

    // 把FriendService对象发布到rpc节点上
    // provider是一个网络服务对象
    RpcProvider provider;
    provider.NotifyService(new FriendService());
    // 通过NotifyService发布服务节点

    // 启动一个rpc服务节点，Run以后，进程进入阻塞状态
    provider.Run();
    return 0;
}