cmake_minimum_required(VERSION 3.12)

project(slimvdi CXX)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_DEPRECATE)
    add_compile_definitions(_CRT_NONSTDC_NO_DEPRECATE)
endif()

#add_compile_definitions(_AMD64_)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Add CMake find_package() integration
set(PROJECT_TARGET_NAME "${PROJECT_NAME}")
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(PROJECT_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/generated/${PROJECT_TARGET_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_TARGET_NAME}Targets")
set(NAMESPACE "slimvdi::")

# Source files
#set(LIB_SRC MediaReg.c Random.c cow.c djfile.c djstring.c env.c hddr.c)
set(LIB_SRC vdir.cpp vdiw.cpp vddr.cpp mem.cpp djfile.cpp env.cpp djstring.cpp filename.cpp MediaReg.cpp memfile.cpp)

# Headers
#set(LIB_INST_HEADERS MediaReg.h cow.h djfile.h djstring.h djtypes.h djwarning.h env.h hddr.h ids.h)
set(LIB_INST_HEADERS vdir.h vdiw.h vddr.h vdistructs.h djtypes.h filename.h mem.h djfile.h env.h djstring.h filename.h MediaReg.h memfile.h djwarning.h partinfo.h ids.h)

add_library(${PROJECT_NAME} ${LIB_SRC})

target_include_directories(${PROJECT_NAME} PRIVATE .)

#target_include_directories(${PROJECT_NAME} PRIVATE ./include ./common)
#target_include_directories(${PROJECT_NAME} PRIVATE ./libbfio ./libcdata ./libcerror ./libcfile ./libclocale)
#target_include_directories(${PROJECT_NAME} PRIVATE ./libcnotify ./libcpath ./libcsplit ./libcthreads)
#target_include_directories(${PROJECT_NAME} PRIVATE ./libfcache ./libfdata ./libfvalue ./libuna)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${TARGETS_EXPORT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)

install(FILES ${LIB_INST_HEADERS} DESTINATION include/slimvdi)

# Generate and install slimvdiConfig.cmake
configure_package_config_file("Config.cmake.in" "${PROJECT_CONFIG}" INSTALL_DESTINATION "${CONFIG_INSTALL_DIR}")
install(FILES "${PROJECT_CONFIG}" DESTINATION "${CONFIG_INSTALL_DIR}")

# Generate and install slimvdiTargets*.cmake
install(EXPORT ${TARGETS_EXPORT_NAME}
        NAMESPACE ${NAMESPACE}
        DESTINATION "${CONFIG_INSTALL_DIR}")
