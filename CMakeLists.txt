cmake_minimum_required(VERSION 3.14)
project(video-app C CXX)
set(CMAKE_CXX_STANDARD 14)

#[[This is a bracket comment.
It runs until the close bracket. 
Setup for C++ 14  ]]

add_subdirectory(lib/glfw)

add_definitions(-DGL_SILENCE_DEPERCATION)

if(APPLE)

	list( APPEND EXTRA_LIBS
		"-framework OpenGL"
	)

elseif(WIN32)
	list(APPEND EXTRA_LIBS
	"-lglu32 -opengl32"
	)
	set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc static-libstdc++ -mwindows")
else()

	list(APPEND EXTRA_LIBS
	"-lGL -lGLU -lX11"
	)

endif()

add_executable(Video-App src/main.cpp)
target_link_libraries(Video-App glfw ${EXTRA_LIBS})