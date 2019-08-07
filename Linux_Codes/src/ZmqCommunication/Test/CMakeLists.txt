include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

add_executable(
        client_test
        ${CMAKE_CURRENT_SOURCE_DIR}/../comBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../client.cpp
        main_client.cpp
)

add_executable(
        server_test
        ${CMAKE_CURRENT_SOURCE_DIR}/../comBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../server.cpp
        main_server.cpp
)

target_include_directories(client_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)


target_include_directories(server_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

TARGET_LINK_LIBRARIES(client_test "zmq")
TARGET_LINK_LIBRARIES(server_test "zmq")
