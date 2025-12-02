cmake_minimum_required(VERSION 3.10)
project(AOC_2025 C)

file(GLOB DAY_DIRS RELATIVE ${CMAKE_SOURCE_DIR} "Day*")

foreach(DAY ${DAY_DIRS})
    if (IS_DIRECTORY "${CMAKE_SOURCE_DIR}/${DAY}")
        file(GLOB DAY_SOURCES "${CMAKE_SOURCE_DIR}/${DAY}/*.c")
        foreach(SRC ${DAY_SOURCES})
            get_filename_component(SRC_NAME ${SRC} NAME_WE)
            set(EXEC_NAME "${SRC_NAME}.out")
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${DAY}/build")
            add_executable(${EXEC_NAME} ${SRC})
            message(STATUS "Added executable ${EXEC_NAME} from source: ${SRC}")
        endforeach()

    endif()
endforeach()
