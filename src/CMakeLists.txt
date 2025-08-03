set(SRC_LIST
    mprpcapplication.cc
    rpcprovider.cc
    mprpcconfig.cc
    rpcheader.pb.cc
    mprpcchannel.cc
    mprpccontroller.cc
    logger.cc
    zookeeperutil.cc
) # 手动添加编译文件
# aux_source_directory(. SRC_LIST) # 不能及时对新添加的文件更新导致编译失败
add_library(mprpc ${SRC_LIST}) # 编译成静态库
target_link_libraries(mprpc muduo_net muduo_base pthread zookeeper_mt)

