
foreach(dir ${SOURCE_DIR})
    file(GLOB_RECURSE dir_sources "${dir}/*.c" "${dir}/*.cpp" "${dir}/*.h")
    list(APPEND PROJECT_SOURCES ${dir_sources})
endforeach()

# 清除文件内容
file(REMOVE ${CMAKE_BINARY_DIR}/buildfile.txt)

# 打开一个文件句柄，准备写入
file(WRITE ${CMAKE_BINARY_DIR}/buildfile.txt "")
# 遍历项目源文件列表并将其写入文件
foreach(source ${PROJECT_SOURCES})
    file(APPEND ${CMAKE_BINARY_DIR}/buildfile.txt "${source}\n")
endforeach()

foreach(libary ${STATIC_QUL_LIBS_PATH})
    file(APPEND ${CMAKE_BINARY_DIR}/buildfile.txt "${libary}\n")
endforeach()
# 输出消息，确认已将源文件列表写入文件
message(STATUS "Source and qul libary file list saved to ${CMAKE_BINARY_DIR}/buildfile.txt")

add_definitions(
    -DCPP_NO_HEAP
    -DFSL_RTOS_FREE_RTOS
    -DPRINTF_ADVANCED_ENABLE=0
    -DPRINTF_FLOAT_ENABLE=0
    -DSCANF_ADVANCED_ENABLE=0
    -DSCANF_FLOAT_ENABLE=0
    -DSKIP_SYSCLK_INIT
    -DUSE_SDRAM
    -DSDK_I2C_BASED_COMPONENT_USED
    -DXIP_BOOT_HEADER_DCD_ENABLE=1
    -DXIP_BOOT_HEADER_ENABLE=1
    -DXIP_EXTERNAL_FLASH=1
    -DVGLITE_POINT_FILTERING_FOR_SIMPLE_SCALE
    -DQUL_STD_STRING_SUPPORT
    -DCPU_MIMXRT1176DVMAA_cm7
    -D__USE_CMSIS
    -DQUL_PREPROCESS_CACHE_SIZE=1M
    -DBOARD_MIPI_PANEL_TOUCH_IRQ=GPIO2_Combined_16_31_IRQn
    -DBOARD_MIPI_PANEL_TOUCH_IRQ_HANDLER=GPIO2_Combined_16_31_IRQHandler
    -DLV_USE_GPU_NXP_VG_LITE=1
    -DQUL_STACK_SIZE=32768
)
