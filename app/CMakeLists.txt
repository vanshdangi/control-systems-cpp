add_executable(ControlSystemsApp
    main.cpp
)

target_link_libraries(ControlSystemsApp
    PRIVATE
        ControlSystems
)