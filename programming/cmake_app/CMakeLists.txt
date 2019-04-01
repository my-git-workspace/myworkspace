cmake_minimum_required(VERSION 2.8.9)
project (CMakeTest)
 
#For the shared library:
set ( PROJECT_LINK_LIBS libhello.so )
#link_directories( ~/exploringBB/extras/cmake/studentlib_shared/build )
link_directories( /opt/hello )
 
#For the static library:
#set ( PROJECT_LINK_LIBS libhello.so )
#link_directories( ~/exploringBB/extras/cmake/studentlib_static/build )
 
include_directories( /home/msys/private/programming/hello_shared/include )
 
add_executable( cmakeapp src/main.cpp)
target_link_libraries( cmakeapp ${PROJECT_LINK_LIBS} )
