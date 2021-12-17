cmake_minimum_required(VERSION 3.1)
project(ExamMT)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

set(SOURCES main.cpp Student.cpp Teacher.cpp TicketsDeck.cpp)
set(HEADERS Student.h Teacher.h TicketsDeck.h)

add_executable(exam ${SOURCES} ${HEADERS})
target_link_libraries (exam ${CMAKE_THREAD_LIBS_INIT})
