
# set(SRC_LIST userservice.cc ../user.pb.cc ../../src/mprpcapplication.cc)
set(SRC_LIST friendservice.cc ../friend.pb.cc ../../src/mprpcapplication.cc)

add_executable(provider ${SRC_LIST})

target_link_libraries(provider mprpc protobuf::libprotobuf pthread)