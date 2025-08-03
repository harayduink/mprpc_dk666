#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;
using fixbug::LoginRequest; using std::string;

int main()
{
    // LoginResponse rsp;
    // // rsp.set_errmsg;
    // ResultCode *rc = rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("登陆处理失败了");

    //获取好友列表响应
    GetFriendListsResponse rsp;
    ResultCode *rc = rsp.mutable_result();
    
    rc->set_errcode(0);
    // rc->set_errmsg("获取好友列表失败");

    User* user1 = rsp.add_friend_list();
    user1->set_name("zhang san");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User* user2 = rsp.add_friend_list();
    user2->set_name("li si");
    user2->set_age(22); 
    user2->set_sex(User::MAN);

    std::cout << rsp.friend_list_size() << std::endl;
    
    return 0;
}


int main1()
{

    
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");
    

    string send_str;
    // 从对象数据序列化 =》 char*
    if(req.SerializeToString(&send_str))
    {
        std::cout << send_str.c_str() << std::endl;
    }
    // 从send_str反序列化一个login请求对象
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str))
    {
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
}
// g++ main.cc test.pb.cc -o my_app `pkg-config --cflags --libs protobuf`