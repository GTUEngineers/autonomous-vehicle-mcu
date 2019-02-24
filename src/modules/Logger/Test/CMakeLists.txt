include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}/test/)

add_executable(
        logger_test
        ${CMAKE_CURRENT_SOURCE_DIR}/../ConsoleLog.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../Syslog.cpp
        logger_test.cpp
)

target_include_directories(logger_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)
