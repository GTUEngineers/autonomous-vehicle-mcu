include(GNUInstallDirs)
set(TARGET_NAME "WifiCommunication")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${TARGET_NAME})
find_package(Protobuf REQUIRED)
add_executable(
        client_test
        main_client.cpp
)

add_executable(
        server_test
        main_server.cpp
)

SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR} 
	${CMAKE_BINARY_DIR}/src/ProtoFiles
	${CMAKE_SOURCE_DIR}/src/mcu_communication
        ${CMAKE_SOURCE_DIR}/src/ZmqCommunication
        ${CMAKE_CURRENT_BINARY_DIR}
        )

target_include_directories(client_test PUBLIC
        ${INCLUDEDIRS})


target_include_directories(server_test PUBLIC
        ${INCLUDEDIRS})

TARGET_LINK_LIBRARIES(client_test "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(server_test "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY})
add_subdirectory(WIFI_CLI)
