cmake_minimum_required (VERSION 2.8.11)

project (fileManagerClient LANGUAGES CXX)
add_executable (fileManagerClient mainClient.cpp clientConn.cpp clientConn.h filemanager_stub.cpp filemanager_stub.h filemanager.h filemanager.cpp utils.h utils.cpp)
target_link_libraries(fileManagerClient pthread)
