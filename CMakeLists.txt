CMAKE_MINIMUM_REQUIRED(VERSION 3.10.0)
include(GNUInstallDirs)

################################################################################
# path variables
SET(TOOLS_PATH "${CMAKE_SOURCE_DIR}/make")
SET(PRJ_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/local_build/Output")

IF (NOT EXISTS "${PRJ_OUTPUT_PATH}")
    add_custom_target(build-time-make-directory-OUTPUT-PATH ALL
            COMMAND ${CMAKE_COMMAND} -E make_directory ${PRJ_OUTPUT_PATH})
ENDIF ()

INCLUDE("${TOOLS_PATH}/global_definition.cmake")

################################################################################
SET(OUTPUT_FILENAME ${PRJ_NAME})
SET(TARGET_NAME "${OUTPUT_FILENAME}")

################################################################################
# configure project sources and build target

set(SUB_MODULES "")
LIST(APPEND SUB_MODULES "src/modules/Logger")
LIST(APPEND SUB_MODULES "src/modules/Communication")
LIST(APPEND SUB_MODULES "src/modules/Message")


FOREACH (_prj ${SUB_MODULES})
    add_subdirectory(${_prj})
ENDFOREACH (_prj)


#ADD_EXECUTABLE(${TARGET_NAME} ${SOURCEFILES})
#TARGET_LINK_LIBRARIES(${TARGET_NAME} ${EXTRA_LIBS})

INCLUDE("${TOOLS_PATH}/print_config.cmake")
