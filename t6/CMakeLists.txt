CMAKE_MINIMUM_REQUIRED(VERSION 3.3)
if (${CMAKE_VERSION} VERSION_GREATER 1.6.1)
    message("cmake version ${CMAKE_VERSION}")
endif()
if (NOT ${CMAKE_VERSION} VERSION_LESS 3,5)
    cmake_policy(VERSION 3.5)
endif()

set(LIB_VERSION_MAJOR   1)
set(LIB_VERSION_MINOR   0)
set(LIB_VERSION_PATCH   1)
set(LIB_VERSION "${LIB_VERSION_MINOR}.${LIB_VERSION_MINOR}.${LIB_VERSION_PATCH}")
PROJECT(HELLOLIB  VERSION "${LIB_VERSION}" LANGUAGES NONE)
ENABLE_LANGUAGE(C CXX)
SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
ADD_SUBDIRECTORY(src)
SET(VTK_USE_HYBRID ON CACHE BOOL "doc string")
set(FOO 1)
if (EXISTS ${PROJECT_SOURCE_DIR}/Help.txt AND COMMAND IF)
    message("Help exits")
endif(EXISTS ${PROJECT_SOURCE_DIR}/Help.txt AND COMMAND IF)

# define a simple macro
#macro (assert TEST COMMENT)
#    if (NOT ${TEST})
#        message("Assertion failed: ${COMMENT}")
#    endif (NOT ${TEST})
#endmacro (assert)

# use the macro
set(assertmsg "Unable the find library foo" "test macro argc argv" "1")
find_library(FOO_LIB foo /usr/local/lib)
assert(${FOO_LIB} "1" "2")

#function(DetermineTime _time)
#    # pass the result up to whatever invoked this
#    set(${_time} "1:23:45" PARENT_SCOPE)
#endfunction()

# now use the function we just defined
DetermineTime( current_time)
if(DEFINED current_time)
    message(STATUS "The time is now: ${current_time}")
endif()

set(fooba 0)

if (NOT DEFINED foobar)
    message("foobar is not defined")
endif(NOT DEFINED foobar)

if (NOT DEFINED fooba)
    message("fooba not defined")
endif(NOT DEFINED fooba)

if (NOT 0 AND 0)
    message("This line is never executed")
endif(NOT 0 AND 0)

if (${FOO} LESS 2)
    set(FOO 2)
else (${FOO} LESS 2)
    set(FOO 3)
endif(${FOO} LESS 2)

FUNCTION(foo)
    MESSAGE(${test})
    set(test 2 PARENT_SCOPE)
    MESSAGE(${test})
ENDFUNCTION()

SET(test 1)
foo()
MESSAGE(${test})
set(items_to_buy apple orange pear beer)

foreach(item ${items_to_buy})
    message("Don't forget to buy one ${item}")
endforeach()
option(USE_JPEG "Do you want to use the jpeg library")
message(${USE_JPEG})
set(USE_JPEG ON CACHE BOOL "include jpeg support?")
message(${USE_JPEG})
set(CRYPTOBACKEND "OpenSSL" CACHE STRING "Select a cryptography backend")
set_property(CACHE CRYPTOBACKEND PROPERTY STRINGS "OpenSSL" "LibTomCrypt" "LibDES")
set(FOO ON)
MESSAGE(${FOO})

