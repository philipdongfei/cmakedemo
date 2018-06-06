# the name of the target operating system
set (CMAKE_SYSTEM_NAME Linux)

# which c and c++ compiler to use
set (CMAKE_C_COMPILER /home/philip/eldk-mips/usr/bin/mips_4KC-gcc)
set (CMAKE_CXX_COMPILER
    /home/philip/eldk-mips/usr/bin/mips_4KC-g++)

# location of the target environment
set (CMAKE_FIND_ROOT_PATH /home/philip/eldk-mips/mips_4KC
                         /home/philip/eldk-mips-extra-install)
set (CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set (CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set (CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
