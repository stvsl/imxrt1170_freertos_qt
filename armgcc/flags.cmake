IF(NOT DEFINED FPU)  
    SET(FPU "-mfloat-abi=hard -mfpu=fpv5-d16")  
ENDIF()  

IF(NOT DEFINED SPECS)  
    SET(SPECS "--specs=nosys.specs")  
ENDIF()  

IF(NOT DEFINED DEBUG_CONSOLE_CONFIG)  
    SET(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1")  
ENDIF()  
# -flto -fuse-linker-plugin \
SET(CMAKE_ASM_FLAGS_DEBUG " \
    ${CMAKE_ASM_FLAGS_DEBUG} \
    -DDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -mcpu=cortex-m7 \
    -mthumb \
    ${FPU} \
")
SET(CMAKE_ASM_FLAGS_RELEASE " \
    ${CMAKE_ASM_FLAGS_RELEASE} \
    -DNDEBUG \
    -D__STARTUP_CLEAR_BSS \
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -mcpu=cortex-m7 \
    -mthumb \
    ${FPU} \
")

SET(CMAKE_C_FLAGS_DEBUG " \
    ${CMAKE_C_FLAGS_DEBUG} \
    -D__NEWLIB__ \
    -DDEBUG \
    -DCPU_MIMXRT1176DVMAA_cm7 \
    -DMCUXPRESSO_SDK \
    -DSERIAL_PORT_TYPE_UART=1 \
    -DSDK_OS_FREE_RTOS \
    -ggdb \
    -Ofast \
    -mcpu=cortex-m7 \
    -Wall \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
    -flto -ffat-lto-objects \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
    
")
SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    -D__NEWLIB__ \
    -DNDEBUG \
    -DCPU_MIMXRT1176DVMAA_cm7 \
    -DMCUXPRESSO_SDK \
    -DSERIAL_PORT_TYPE_UART=1 \
    -DSDK_OS_FREE_RTOS \
    -Ofast \
    -mcpu=cortex-m7 \
    -Wall \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -std=gnu99 \
    -flto -ffat-lto-objects \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
    
")

SET(CMAKE_CXX_FLAGS_DEBUG " \
    -std=gnu++14 \
    ${CMAKE_CXX_FLAGS_DEBUG} \
    -DDEBUG \
    -DCPU_MIMXRT1176DVMAA_cm7 \
    -DMCUXPRESSO_SDK \
    -DSERIAL_PORT_TYPE_UART=1 \
    -ggdb \
    -Ofast \
    -mcpu=cortex-m7 \
    -Wall \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    -flto -ffat-lto-objects \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
    
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    -std=gnu++14 \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    -DNDEBUG \
    -DCPU_MIMXRT1176DVMAA_cm7 \
    -DMCUXPRESSO_SDK \
    -DSERIAL_PORT_TYPE_UART=1 \
    -Ofast \
    -mcpu=cortex-m7 \
    -Wall \
    -mthumb \
    -MMD \
    -MP \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    -flto -ffat-lto-objects \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
    
")


SET(CMAKE_EXE_LINKER_FLAGS_DEBUG " \
    ${CMAKE_EXE_LINKER_FLAGS_DEBUG} \
    -ggdb \
    -mcpu=cortex-m7 \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Xlinker \
    --gc-sections \
    -Xlinker \
    -static \
    -Xlinker \
    -z \
    -Xlinker \
    muldefs \
    -Xlinker \
    -Map=output.map \
    -Wl,--print-memory-usage \
    -Xlinker \
    -cref \
    -Xlinker \
    -flto -ffat-lto-objects \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/../platform/platform/boards/nxp/mimxrt1170-evkb-freertos/cmake/armgcc/MIMXRT1176xxxxx_cm7_flexspi_nor_sdram.ld\" -static \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    -mcpu=cortex-m7 \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -ffreestanding \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Xlinker \
    --gc-sections \
    -Xlinker \
    -static \
    -Xlinker \
    -z \
    -Xlinker \
    muldefs \
    -Xlinker \
    -Map=output.map \
    -Wl,--print-memory-usage \
    -Xlinker \
    -cref \
    -Xlinker \
    -flto -ffat-lto-objects \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/../platform/platform/boards/nxp/mimxrt1170-evkb-freertos/cmake/armgcc/MIMXRT1176xxxxx_cm7_flexspi_nor_sdram.ld\" -static \
")
