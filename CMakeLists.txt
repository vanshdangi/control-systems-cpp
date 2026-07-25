cmake_minimum_required(VERSION 3.20)

project(ControlSystems LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(ControlSystems
    # Controllers
    src/controllers/p_controller.cpp
    src/controllers/pi_controller.cpp
    src/controllers/pd_controller.cpp
    src/controllers/pid_controller.cpp

    # Filters
    src/filters/low_pass_filter.cpp

    # Plants
    src/plants/point_mass.cpp
    src/plants/spring_mass_damper.cpp
    src/plants/dc_motor.cpp

    # Math
    src/math/integrator.cpp
    src/math/numerical_derivative.cpp

    # Utils
    src/utils/csv_logger.cpp
)

target_include_directories(ControlSystems
    PUBLIC
        include/control_systems
)

if(MSVC)
    target_compile_options(ControlSystems PRIVATE /W4)
else()
    target_compile_options(ControlSystems PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

enable_testing()

add_subdirectory(app)
add_subdirectory(examples)
add_subdirectory(tests)