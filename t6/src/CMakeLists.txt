FIND_PACKAGE(HELLO)

IF(HELLO_FOUND)
    cmake_policy(PUSH)
    cmake_policy(SET CMP0003 OLD) # use old-style link for now
    ADD_EXECUTABLE(hello main.c)
    cmake_policy(POP)
    INCLUDE_DIRECTORIES(${HELLO_INCLUDE_DIR})
    include (FindPNG)
    message("PNG_FOUND ${PNG_FOUND}")
    link_directories(/usr/lib)
    message(${HELLO_LIBRARY})
    target_link_libraries(hello libhello.so)
    #TARGET_LINK_LIBRARIES(hello ${HELLO_LIBRARY} ${PNG_LIBRARIES} hello)
    message("PNG_LIBRARIES ${PNG_LIBRARIES}")
ENDIF(HELLO_FOUND)

