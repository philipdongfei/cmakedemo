# PNG depends on Zlib

if (ZLIB_FOUND)
    find_path (PNG_PNG_INCLUDE_DIR png.h
        /usr/local/include
        /usr/include
        )
    find_library (PNG_LIBRARY png
        /usr/lib
        /usr/local/lib
        )
    if (PNG_LIBRARY)
        if (PNG_PNG_INCLUDE_DIR)
            #png.h includes zlib.h Sigh.
            set (PNG_INCLUDE_DIR
                ${PNG_PNG_INCLUDE_DIR} ${ZLIB_INCLUDE_DIR})
            set (PNG_LIBRARIES ${PNG_LIBRARY} ${ZLIB_LIBRARY})
            set (PNG_FOUND "YES")

            if (CYGWIN)
                if (BUILD_SHARED_LIBS)
                    # NO need to define PNG_USE_DLL here, because
                    # it's default for Cygwin.
                else (BUILD_SHARED_LIBS)
                    set (PNG_DEFINITIONS -DPNG_STATIC)
                endif(BUILD_SHARED_LIBS)
            endif (CYGWIN)
        endif()
    endif()
endif()
