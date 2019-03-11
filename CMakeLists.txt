cmake_minimum_required(VERSION 3.1)

# I don't even know how to use good half of this
# PlsDeleteMyLife

project(main.cpp)

#find_library(PTHREAD_LIBRARY pthread)
#find_library(PCRE_LIBRARY pcre)

#add_library(src/ header.hpp)

include_directories(include)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(SOURCE src/header2.hpp)
set(SOURCE src/header3.hpp)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")


add_executable(main src/main.cpp src/header2.hpp src/header3.hpp)

#target_link_libraries(main ${PTHREAD_LIBRARY} ${PCRE_LIBRARY})
