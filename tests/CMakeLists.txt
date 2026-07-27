include(FetchContent)
cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

function(add_control_systems_test TEST_NAME TEST_FILE)
    add_executable(${TEST_NAME}
        ${TEST_FILE}
    )

    target_link_libraries(${TEST_NAME}
        PRIVATE
            ControlSystems
            GTest::gtest_main
    )

    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    )

    gtest_discover_tests(${TEST_NAME})
endfunction()

# Controllers
add_control_systems_test(PControllerTest controllers/p_controller_test.cpp)
add_control_systems_test(PIControllerTest controllers/pi_controller_test.cpp)
add_control_systems_test(PDControllerTest controllers/pd_controller_test.cpp)
add_control_systems_test(PIDControllerTest controllers/pid_controller_test.cpp)

# Plants
add_control_systems_test(PointMassTest plants/point_mass_test.cpp)
add_control_systems_test(SpringMassDamperTest plants/spring_mass_damper_test.cpp)
add_control_systems_test(DCMotorTest plants/dc_motor_test.cpp)

# Utils
add_control_systems_test(CSVLoggerTest utils/csv_logger_test.cpp)