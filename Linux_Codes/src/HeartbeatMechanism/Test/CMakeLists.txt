include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

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

target_include_directories(heartbeatMechanism_test_car PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)


target_include_directories(heartbeatMechanism_test_station PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

TARGET_LINK_LIBRARIES(heartbeatMechanism_main_station "CommonLib" "zmq" "pthread" "ZmqCommunication" ${PROTOBUF_LIBRARY})
TARGET_LINK_LIBRARIES(heartbeatMechanism_main_car "CommonLib" "zmq" "pthread" "ZmqCommunication" ${PROTOBUF_LIBRARY}) 
