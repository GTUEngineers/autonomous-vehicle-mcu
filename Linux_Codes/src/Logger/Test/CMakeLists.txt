include(GNUInstallDirs)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/test/)

add_executable(
        logger_test
        logger_test.cpp
)

target_include_directories(logger_test PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../)

TARGET_LINK_LIBRARIES(logger_test "Logger")
