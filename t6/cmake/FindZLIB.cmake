find_path (ZLIB_INCLUDE_DIR zlib.h
    /usr/local/include
    /usr/include
    )

find_library (ZLIB_LIBRARY zlib
    /usr/lib
    /usr/local/lib
    )

if (ZLIB_LIBRARY)
    if (ZLIB_INCLUDE_DIR)
        set (ZLIB_FOUND "YES")
    endif()
endif()
