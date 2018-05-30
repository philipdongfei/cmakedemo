FIND_PATH(HELLO_INCLUDE_DIR hello.h /usr/include/hello /usr/local/include/hello)
FIND_LIBRARY(HELLO_LIBRARY NAMES hello PATH /usr/lib /usr/local/lib)
IF(HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
    SET(HELLO_FOUND TRUE)
ENDIF(HELLO_INCLUDE_DIR AND HELLO_LIBRARY)
IF(HELLO_FOUND)
    IF(NOT HELLO_FIND_QUIETLY)
        MESSAGE(STATUS "Found Hello: ${HELLO_LIBRARY}")
    ENDIF(NOT HELLO_FIND_QUIETLY)
ELSE(HELLO_FOUND)
    IF(HELLO_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR "Could not find hello library")
    ENDIF(HELLO_FIND_REQUIRED)
ENDIF(HELLO_FOUND)
#define a macro that takes at least two arguments
#(the formal arguments) plus an optional third argument


# define a simple macro
macro (assert TEST COMMENT)
    if (NOT ${TEST})
        message("Assertion failed: ${COMMENT}")
        # if called with three arguments then also write the 
        # message to a file specified as the third argument
        if (${ARGC} MATCHES 3)
            file (APPEND ${ARGV2} "Assertion failed: ${COMMENT}")
        endif (${ARGC} MATCHES 3)
    
    endif (NOT ${TEST})
endmacro (assert)


function(DetermineTime _time)
    # pass the result up to whatever invoked this
    set(${_time} "1:23:45" PARENT_SCOPE)
endfunction()
