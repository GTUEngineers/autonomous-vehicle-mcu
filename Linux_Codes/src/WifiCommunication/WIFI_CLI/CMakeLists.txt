set(TARGET_NAME "WifiCommunication_CLI")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${TARGET_NAME})

add_executable(
        wifi_cli_test
	WIFI_CommandLineInterface.cpp
)


SET(SOURCEFILES
	WIFI_CommandLineInterface.cpp
    	${CMAKE_SOURCE_DIR}/src/WifiCommunication/main_cient.cpp
    	${CMAKE_SOURCE_DIR}/src/WifiCommunication/main_server.cpp
        )

SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_BINARY_DIR}/src/ProtoFiles
	${CMAKE_SOURCE_DIR}/src/ZmqCommunication
        ${CMAKE_SOURCE_DIR}/src/mcu_communication
	${CMAKE_SOURCE_DIR}/src/CommonLib
        ${CMAKE_CURRENT_BINARY_DIR}
        )


#include_directories(${INCLUDEDIRS})

target_include_directories(wifi_cli_test PUBLIC
        ${INCLUDEDIRS})

TARGET_LINK_LIBRARIES(wifi_cli_test "CommonLib" "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY})

