set(EXAMPLES
    p_point_mass
    pid_point_mass
    pid_spring_mass_damper
    pid_dc_motor_position
    pid_dc_motor_speed
)

foreach(example ${EXAMPLES})
    add_executable(${example}
        ${example}.cpp
    )

    target_link_libraries(${example}
        PRIVATE
            ControlSystems
    )

    set_target_properties(${example} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
    )
endforeach()