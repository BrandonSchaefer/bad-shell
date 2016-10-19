find_package (PkgConfig)

set (BAD_SHELL_REQUIRED
        miral
    )

pkg_check_modules(BAD_SHELL REQUIRED ${BAD_SHELL_REQUIRED})

set (BAD_SHELL_LOADER_SRC
     bad_window_manager_policy.cpp
     main.cpp
    )

set (BAD_SHELL_LOADER_HDR
     bad_window_manager_policy.h
    )

include_directories (${BAD_SHELL_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_executable (bad-shell ${BAD_SHELL_LOADER_SRC} ${BAD_SHELL_LOADER_HDR})

target_link_libraries (bad-shell ${BAD_SHELL_LIBRARIES} ${BAD_SHELL_LDFLAGS})
