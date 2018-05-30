cmake_minimum_required(VERSION 2.7)
project (testfoobar)

include (CheckIncludeFiles)
include (CheckLibraryExists)
include (CheckSymbolExists)
include (CheckTypeSize)

set (INCLUDES "")
CHECK_INCLUDE_FILES("${INCLUDES};winsock.h" HAVE_WINSOCK_H)

if (HAVE_WINSOCK_H)
    set (INCLUDES ${INCLUDES} winsock.h)
endif(HAVE_WINSOCK_H)

CHECK_INCLUDE_FILES ("${INCLUDES};io.h" HAVE_IO_H)
if (HAVE_IO_H)
    set(INCLUDES ${INCLUDES} io.h)
endif(HAVE_IO_H)

set(LIBS "")
CHECK_LIBRARY_EXISTS("dl;${LIBS}" dlopen "" HAVE_LIBDL)

if (HAVE_LIBDL)
    set(LIBS ${LIBS} dl)
endif(HAVE_LIBDL)

CHECK_LIBRARY_EXISTS("usb;${LIBS}" gethostname "" HAVE_LIBUCB)
if (HAVE_LIBUCB)
    set(LIBS ${LIBS} ucb)
endif(HAVE_LIBUCB)

set(CMAKE_REQUIRED_LIBRARIES ${LIBS})
CHECK_SYMBOL_EXISTS(socket "${INCLUDES}" HAVE_SOCKET)
CHECK_SYMBOL_EXISTS(poll   "${INCLUDES}" HAVE_POLL)

CHECK_TYPE_SIZE (int SIZEOF_INT)
CHECK_TYPE_SIZE (size_t SIZEOF_SIZE_T)
find_package(OpenGL)
message(${OpenGL_DIR})
