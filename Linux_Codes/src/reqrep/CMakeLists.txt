include(GNUInstallDirs)
set(TARGET_NAME "ReqRep")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME})

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
	${CMAKE_SOURCE_DIR}/src/ZmqCommunication
        )

target_include_directories(client_test PUBLIC
        ${INCLUDEDIRS})


target_include_directories(server_test PUBLIC
        ${INCLUDEDIRS})

TARGET_LINK_LIBRARIES(client_test "zmq" "ZmqCommunication")
TARGET_LINK_LIBRARIES(server_test "zmq" "ZmqCommunication")
