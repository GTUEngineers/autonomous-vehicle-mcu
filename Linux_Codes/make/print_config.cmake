MESSAGE("------------------------------------------------------------")
MESSAGE(STATUS "Project name:                  ${PROJE_NAME}")
MESSAGE(STATUS "Description :                  ${DESCRIPTION}")
MESSAGE(STATUS "Version     :                  ${VERSION}")

IF(C_STANDARD)
    MESSAGE(STATUS "C Standard  :                  ${C_STANDARD}") 
ENDIF(C_STANDARD)

IF(CXX_STANDARD)
    MESSAGE(STATUS "C++ Standard:                  ${CXX_STANDARD}")
ENDIF(CXX_STANDARD)