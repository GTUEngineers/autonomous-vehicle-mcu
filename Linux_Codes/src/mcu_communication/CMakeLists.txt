set(TARGET_NAME "MCU_Communication")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${TARGET_NAME})
find_package(Protobuf REQUIRED)

SET(SOURCEFILES
	CommunicationMechanism.cpp
	UARTCommunication.cpp
        mcu_communication_service.cpp
        UARTMessageBuilder.cpp
        )


SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR} 
	${CMAKE_BINARY_DIR}/src/ProtoFiles
	${CMAKE_SOURCE_DIR}/src/ZmqCommunication
        ${CMAKE_CURRENT_BINARY_DIR}
        )


#include_directories(${INCLUDEDIRS})

add_executable(
        ${TARGET_NAME} 
        ${SOURCEFILES}
)

add_executable(
	cli_test
        cli.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../
)
target_include_directories(${TARGET_NAME} PUBLIC ${INCLUDEDIRS})
target_include_directories(cli_test PUBLIC ${INCLUDEDIRS})
#TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY})
#ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY} "pthread")
TARGET_LINK_LIBRARIES(cli_test "zmq" "ZmqCommunication" ${PROTOBUF_LIBRARY} "pthread")

