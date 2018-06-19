CMAKE_MINIMUM_REQUIRED(VERSION 3.3)

PROJECT(HELLO)
ENABLE_LANGUAGE(CXX C)

SET(SRC_LIST main.c)
MESSAGE(STATUS "This is BINARY dir " ${PROJECT_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${PROJECT_SOURCE_DIR})
message(STATUS "CTEST_COMMAND:" ${CTEST_COMMAND})
ENABLE_TESTING()
include(CTest)
option (DEBUG_BUILD "Build with extra debug printf message." )
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
if (DEBUG_BUILD)
    add_definitions(-DDEBUG_BUILD)
endif(DEBUG_BUILD)
ADD_EXECUTABLE(hello ${SRC_LIST})
message(STATUS "executable dir" ${EXECUTABLE_OUTPUT_PATH})
message(STATUS "cmake binary dir" ${CMake_SOURCE_DIR})

message(STATUS "cmake ctest command" ${CMAKE_CTEST_COMMAND})
#add_test(NAME hello
#         COMMAND ${EXECUTABLE_OUTPUT_PATH}/hello)
add_test (hello ${CMAKE_CTEST_COMMAND}
    --build-and-test "${CMake_SOURCE_DIR}/Tests/Hello"
                     "${CMake_BINARY_DIR}/Tests/Hello"
    --build-generator ${CMAKE_GENERATOR}
    --build-makeprogram ${CMAKE_MAKE_PROGRAM}
    --build-project  Hello
    --test-command   hello)
##set (passRegex "^Test passed" "^All ok")
##set (failRegex "Error" "Fail")
##set_property (TEST hello
##              PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
##set_property (TEST hello
##              PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")

if (CMAKE_SYSTEM MATCHES Windows)
    message(STATUS "Target system is Windows")
endif()
if (CMAKE_HOST_SYSTEM MATCHES Linux)
    message(STATUS "Build host runs Linux")
endif()

message("${CMAKE_SYSTEM_NAME}-COMPILER_ID-${CMAKE_SYSTEM_PROCESSOR}.cmake")

#get_target_property (hello EXE_LOC LOCATION)
#set(EXE_LOC ${ARCHIVE_OUTPUT_DIRECTORY})
#message("EXE_LOC" ${EXE_LOC})


configure_file (
    ${PROJECT_SOURCE_DIR}/projectConfigure.h.in
    ${PROJECT_SOURCE_DIR}/projectConfigure.h)

if (HAS_FOOBAR_CALL)
    message("HAS_FOOBAR_CALL is true")
endif(HAS_FOOBAR_CALL)
message("CMAKE_CFG_INTDIR:"${CMAKE_CFG_INTDIR})

install (DIRECTORY  DESTINATION share/myproject/user)
install (DIRECTORY data/scripts DESTINATION share/myproject
         FILE_PERMISSIONS
         OWNER_READ OWNER_EXECUTE OWNER_WRITE
         GROUP_READ GROUP_EXECUTE
         WORLD_READ WORLD_EXECUTE
         DIRECTORY_PERMISSIONS
         OWNER_READ OWNER_EXECUTE OWNER_WRITE
         GROUP_READ GROUP_EXECUTE GROUP_WRITE
         WORLD_READ WORLD_EXECUTE)
install (DIRECTORY data/icons DESTINATION share/myproject
    PATTERN "CVS" EXCLUDE
    PATTERN "*.txt"
      PERMISSIONS OWNER_READ OWNER_WRITE
    PATTERN "*.sh"
      PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
install (SCRIPT message.cmake)
include (CPack)
