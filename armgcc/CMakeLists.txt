# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
  message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
SET(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})

project(freertos_hello_cm7)

set(MCUX_BUILD_TYPES debug release)

set(MCUX_SDK_PROJECT_NAME freertos_hello_cm7.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath ${ProjDirPath}/../../../../../..)
endif()

set(SOURCE_DIR 
    ${ProjDirPath}/../device
    ${ProjDirPath}/../src
)

set(QUL_LIB_TYPE "Debug")

include(${ProjDirPath}/flags.cmake)
include(${ProjDirPath}/config.cmake)
include(${ProjDirPath}/qul.cmake)
include(${ProjDirPath}/projectconfig.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME} 
${PROJECT_SOURCES}
"${ProjDirPath}/../evkmimxrt1170_connect_cm4_cm7side.jlinkscript"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../dcd.c"
"${ProjDirPath}/../dcd.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../clock_config.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
    ${ProjDirPath}/src/..
    $ENV{QUL_ROOT}/include
    $ENV{QUL_ROOT}/src/3rdparty/qoi
    $ENV{QUL_ROOT}/src/3rdparty/minihdlc
    $ENV{QUL_ROOT}/src/3rdparty/nanopb
    ${ProjDirPath}/../platform/platform/common
    ${ProjDirPath}/../platform/platform/boards/nxp/mimxrt1170-evkb-freertos
    ${ProjDirPath}/../platform/platform/boards/nxp/mimxrt1170-evkb-freertos/display
)

set_source_files_properties("${ProjDirPath}/../FreeRTOSConfig.h" PROPERTIES COMPONENT_CONFIG_FILE "middleware_freertos-kernel_template")

include(${SdkRootDirPath}/devices/MIMXRT1176/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${STATIC_QUL_LIBS_PATH})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} 
    POST_BUILD 
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} 
    ${EXECUTABLE_OUTPUT_PATH}/freertos_hello.bin
)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;${EXECUTABLE_OUTPUT_PATH}/freertos_hello.bin")