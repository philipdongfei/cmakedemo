set (CMAKE_CXX_CREATE_SHARED_LIBRARY
    "<CMAKE_CXX_COMPILER> ${CMAKE_START_TEMP_FILE}-e<TARGET>
-tWD <LINK_FLAGS> -tWR <LINK_LIBRARIES>
<OBJECTS>${CMAKE_END_TEMP_FILE}"
"implib -c -w <TARGET_BASE>.lib <TARGET_BASE>.dll"
)

set (CMAKE_CXX_CREATE_SHARED_MODULE
    ${CMAKE_CXX_CREATE_SHARED_LIBRARY})

# create a c shared library
set (CMAKE_C_CREATE_SHARED_LIBRARY
    "<CMAKE_C_COMPILER> ${CMAKE_START_TEMP_FILE}-e<TARGET> -tWD
    <LINK_FLAGS> -tWR <LINK_LIBRARIES>
    <OBJECTS>${CMAKE_END_TEMP_FILE}"
    "implib -c -w <TARGET_BASE>.lib <TARGET_BASE>.dll"
    )

# create a c++ static library
set (CMAKE_CXX_CREATE_STATIC_LIBRARY "tlib
${CMAKE_START_TEMP_FILE}/p512 <LINK_FLAGS> /a <TARGET_QUOTED>
<OBJECTS_QUOTED>${CMAKE_END_TEMP_FILE}")

# compile a c++ file into an object file
set (CMAKE_CXX_COMPILE_OBJECT
    "<CMAKE_CXX_COMPILER> ${CMAKE_START_TEMP_FILE}-DWIN32 -P
<FLAGS> -o<OBJECT> -c <SOURCE>${CMAKE_END_TEMP_FILE}")