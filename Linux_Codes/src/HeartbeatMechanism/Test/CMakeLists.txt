include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

add_executable(
        heartbeatMechanism_test_station
        ${CMAKE_CURRENT_SOURCE_DIR}/../comBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../heartbeatsMechanisim.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../publisher.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../subscriber.cpp
        main_server.cpp
)

add_executable(
        heartbeatMechanism_test_arac
        ${CMAKE_CURRENT_SOURCE_DIR}/../comBase.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../heartbeatsMechanisim.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../publisher.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../subscriber.cpp
        main_arac.cpp
)

target_include_directories(heartbeatMechanism_test_arac PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)


target_include_directories(heartbeatMechanism_test_station PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

TARGET_LINK_LIBRARIES(heartbeatMechanism_test_station "zmq" "pthread")
TARGET_LINK_LIBRARIES(heartbeatMechanism_test_arac "zmq" "pthread")
