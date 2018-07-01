cmake_minimum_required(VERSION 2.8.9)
#Name your project
project(a.out)

#Bring the headers, such as nlp.h into the project
include_directories(include)

#The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")

#Specify that this project is an executable and is compiled from SOURCES
add_executable(${PROJECT_NAME} main.c ${SOURCES})

#Uncomment if you want to link library
#target_link_libraries(a.out m)

#Set compiler flags
SET(CMAKE_C_FLAGS "-std=c11")
