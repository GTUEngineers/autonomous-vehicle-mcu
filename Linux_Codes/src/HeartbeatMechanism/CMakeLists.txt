include(GNUInstallDirs)

set(TARGET_NAME "HeartbeatMechanism")
PROJECT(${TARGET_NAME} CXX C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${TARGET_NAME}/)

SET(SOURCEFILES
	heartbeatsMechanism_car.cpp
	heartbeatsMechanism_station.cpp
        )
SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_SOURCE_DIR}/src/ZmqCommunication
	${CMAKE_SOURCE_DIR}/src/CommonLib
	${CMAKE_BINARY_DIR}/src/ProtoFiles
	${CMAKE_SOURCE_DIR}/src/mcu_communication
	${CMAKE_CURRENT_BINARY_DIR}
        )

add_executable(
        heartbeatMechanism_main_station
        main_station.cpp
        ${CMAKE_SOURCE_DIR}/src/HeartbeatMechanism/heartbeatsMechanism_station.cpp
)

add_executable(
        heartbeatMechanism_main_car
        main_car.cpp
        ${CMAKE_SOURCE_DIR}/src/HeartbeatMechanism/heartbeatsMechanism_car.cpp
)

target_include_directories(heartbeatMechanism_main_car PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)


target_include_directories(heartbeatMechanism_main_station PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

include_directories(${INCLUDEDIRS})
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
TARGET_LINK_LIBRARIES(${TARGET_NAME} "CommonLib" "zmq" "pthread" "ZmqCommunication" ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(heartbeatMechanism_main_station "CommonLib" "zmq" "pthread" "ZmqCommunication" ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(heartbeatMechanism_main_car "CommonLib" "zmq" "pthread" "ZmqCommunication" ${PROTOBUF_LIBRARY}) 
#add_subdirectory(Test)

