
# set(SRC_LIST calluserservice.cc ../user.pb.cc ../../src/mprpcapplication.cc)

set(SRC_LIST callfriendservice.cc ../friend.pb.cc ../../src/mprpcapplication.cc)


add_executable(consumer ${SRC_LIST})

target_link_libraries(consumer mprpc protobuf::libprotobuf pthread)