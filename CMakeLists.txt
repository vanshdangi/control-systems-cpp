cmake_minimum_required(VERSION 3.20)

project(ControlSystems LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(ControlSystems
    # Controllers
    src/controllers/p_controller.cpp
    src/controllers/pi_controller.cpp
    src/controllers/pd_controller.cpp

    # Plants
    src/plants/point_mass.cpp
    src/plants/spring_mass_damper.cpp

    # Maths
    src/math/integrator.cpp
    src/math/numerical_derivative.cpp
)

# Public headers
target_include_directories(ControlSystems
    PUBLIC
        include/control_systems
)

# Executable
add_executable(ControlSystemsApp
    app/main.cpp
)

target_link_libraries(ControlSystemsApp
    PRIVATE ControlSystems
)

# Compiler warnings
if(MSVC)
    target_compile_options(ControlSystems PRIVATE /W4)
else()
    target_compile_options(ControlSystems PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()