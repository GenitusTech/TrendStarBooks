cmake_minimum_required(VERSION 3.15.0...4.0.0)
project(
    trend_star_books
    VERSION 0.1.0
    LANGUAGES C
    DESCRIPTION "A secure C microservice"
)

#───────────────────────────────────────────────────────────────────────────────
# [1] SECURITY & COMPILER HARDENING
#───────────────────────────────────────────────────────────────────────────────
set(CMAKE_C_STANDARD 11)              # C11 for better type safety
set(CMAKE_C_STANDARD_REQUIRED ON)     # Enforce C11 compliance
set(CMAKE_C_EXTENSIONS OFF)           # Disable compiler extensions (strict mode)

# Security-hardened compiler flags
add_compile_options(
    -Wall -Wextra -Wpedantic          # Maximum warnings
    -Werror=implicit-function-declaration  # No implicit functions
    -Werror=incompatible-pointer-types     # Strict pointer typing
    -fstack-protector-strong          # Stack smashing protection
    -D_FORTIFY_SOURCE=2               # Buffer overflow checks
    -fPIE                             # Position Independent Executable
    -O2                               # Optimizations without sacrificing security
)

# Security-hardened linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-z,now -Wl,-z,relro -pie")

# Policy settings for security
cmake_policy(SET CMP0076 NEW) # Use absolute install paths
cmake_policy(SET CMP0077 NEW) # Honor enabled languages

#───────────────────────────────────────────────────────────────────────────────
# [2] DEPENDENCY MANAGEMENT (SECURE VERSIONS)
#───────────────────────────────────────────────────────────────────────────────

# (A) libcurl (HTTPS/HTTP)
find_package(CURL 8.12.1 REQUIRED)
if(NOT CURL_FOUND)
    message(FATAL_ERROR "libcurl >= 8.12.1 required (missing or too old)")
endif()

# (B) cJSON (JSON parsing)
find_package(cJSON 1.7.18 REQUIRED)
if(NOT cJSON_FOUND)
    message(FATAL_ERROR "cJSON >= 1.7.18 required (missing or too old)")
endif()
# (C) libwebsockets (WebSockets)
# find_package(WebSockets 4.0.0 REQUIRED) # libwebsockets
# (D) MySQL Connector/C (MySQL client)
# find_package(MySQL REQUIRED) # mariadb-connector-c

#───────────────────────────────────────────────────────────────────────────────
# [3] MAIN EXECUTABLE (SECURE CONFIG)
#───────────────────────────────────────────────────────────────────────────────

add_executable(${PROJECT_NAME}
    src/main.c
)

#───────────────────────────────────────────────────────────────────────────────
# [4] SECURE TARGET PROPERTIES
#───────────────────────────────────────────────────────────────────────────────

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE ON    # ASLR compatibility
)

#───────────────────────────────────────────────────────────────────────────────
# [5] SECURE LINKING
#───────────────────────────────────────────────────────────────────────────────

target_link_libraries(${PROJECT_NAME} PRIVATE
    CURL::libcurl                     # Typed CMake target (modern)
    # cJSON::cJSON                      # Typed CMake target (modern)
    # WebSockets::WebSockets            # Typed CMake target (modern)
    # MySQL::MySQL                      # Typed CMake target (modern)
)

#───────────────────────────────────────────────────────────────────────────────
# [6] SECURE INSTALLATION
#───────────────────────────────────────────────────────────────────────────────
install(TARGETS ${PROJECT_NAME}
    DESTINATION bin
    PERMISSIONS
        OWNER_READ OWNER_WRITE OWNER_EXECUTE
        GROUP_READ GROUP_EXECUTE
        WORLD_READ WORLD_EXECUTE       # Least privilege
)

#───────────────────────────────────────────────────────────────────────────────
# [7] SECURITY CHECKS (OPTIONAL BUT RECOMMENDED)
#───────────────────────────────────────────────────────────────────────────────
# (A) Static analysis with cppcheck
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    add_custom_target(security_scan
        COMMAND ${CPPCHECK}
            --enable=warning,performance,portability,style
            --error-exitcode=1
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        COMMENT "Running cppcheck for security analysis"
    )
endif()

# (B) Flawfinder (security vulnerability scanner)
find_program(FLAWFINDER flawfinder)
if(FLAWFINDER)
    add_custom_target(flawfinder_scan
        COMMAND ${FLAWFINDER} --quiet --minlevel=3 ${CMAKE_CURRENT_SOURCE_DIR}/src
        COMMENT "Running flawfinder for security flaws"
    )
endif()

#───────────────────────────────────────────────────────────────────────────────
# [8] UNIT TESTS (SECURE TEST BUILD)
#───────────────────────────────────────────────────────────────────────────────
include(CTest)
if(BUILD_TESTING)
    enable_testing()
    add_executable(${PROJECT_NAME}_tests
        tests/client.c
        # tests/test_json.c
        # tests/test_websocket.c
        # tests/test_mysql.c
    )
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE
        CURL::libcurl               # Typed CMake target (modern)
    )
    add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
endif()

#───────────────────────────────────────────────────────────────────────────────
# [9] PACKAGING (DEB/RPM WITH SECURE PERMISSIONS)
#───────────────────────────────────────────────────────────────────────────────
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VENDOR "GenitusTech")
set(CPACK_PACKAGE_CONTACT "contact@genitus.tech")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)  # Auto-detect runtime deps
include(CPack)
