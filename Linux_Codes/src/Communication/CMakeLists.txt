
set(TARGET_NAME "Communication")
PROJECT(${TARGET_NAME} CXX C ASM)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PRJ_OUTPUT_PATH}/${PROJECT_NAME}/)

SET(SOURCEFILES
        AbstractCommunication.cpp
        Client.cpp
        Server.cpp
        )
SET(INCLUDEDIRS
        ${CMAKE_CURRENT_LIST_DIR}
        )
ADD_LIBRARY(${TARGET_NAME} STATIC ${SOURCEFILES})
#TARGET_LINK_LIBRARIES(${TARGET_NAME} "")
add_subdirectory(Test)
