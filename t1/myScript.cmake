set (CTEST_SOURCE_DIRECTORY  ~/CodeDemo/cmakedemo/t1)
set (CTEST_BINARY_DIRECTORY  ~/CodeDemo/cmakedemo/t1/build)

set (CTEST_COMMAND
    "\"${CTEST_EXECUTABLE_NAME}\" -D Nightly"
    )

set (CTEST_CMAKE_COMMAND
    "\"${CMAKE_EXECUTABLE_NAME}\""
    )
