cmake_minimum_required(VERSION 3.9)
project(ft_nm)

set(CMAKE_C99_STANDARD 17)

# Rigourous Error management
set(CMAKE_C_FLAGS "-Wall -Werror -Wall")

# Including *.c and *.h project files
FILE(GLOB_RECURSE SH_SOURCE
        src/shared/*.c)

FILE(GLOB_RECURSE NM_SOURCE
        src/ft_nm/*.c
        includes/*.h)

FILE(GLOB_RECURSE OT_SOURCE
        src/ft_otool/*.c
        includes/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/nm_otool")
# Build executable
add_executable(ft_nm ${NM_SOURCE} ${SH_SOURCE})

add_executable(ft_otool ${OT_SOURCE} ${SH_SOURCE})

find_library(LIBFT ft libft)

target_link_libraries(ft_nm LINK_PUBLIC ${LIBFT})

