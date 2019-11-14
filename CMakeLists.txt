cmake_minimum_required(VERSION 3.9)
project(ft_ssl)

set(CMAKE_C99_STANDARD 17)

# Rigourous Error management
set(CMAKE_C_FLAGS "-Wall -Werror -Wall")

# Including *.c and *.h project files
File(GLOB_RECURSE SOURCE
        src/*.c
        includes/*.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "~/ft_ssl_md5")
# Build executable
add_executable(ft_ssl
        ${SOURCE})

find_library(LIBFT ft libft)
target_link_libraries(ft_ssl LINK_PUBLIC ${LIBFT})

