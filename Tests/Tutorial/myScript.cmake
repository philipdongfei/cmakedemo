set (CTEST_SOURCE_DIRECTORY ~/CodeDemo/cmakedemo/Test/Tutorial)
set (CTEST_BINARY_DIRECTORY ~/CodeDemo/cmakedemo/Test/Tutorial/build)

set (CTEST_COMMAND
    "\"${CTEST_EXECUTABLE_NAME}\" -D Nightly"
)

set (CTEST_CMAKE_COMMAND
    "\"${CMAKE_EXECUTABLE_NAME}\""
    )

set (CTEST_START_WITH_EMPTY_BINARY_DIRECTORY TRUE)


