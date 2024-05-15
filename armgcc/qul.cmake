if(NOT DEFINED ENV{QUL_ROOT})
message(FATAL_ERROR "QUL_ROOT not defined!")
endif()
message(STATUS "QUL_ROOT: $ENV{QUL_ROOT}")

if(NOT DEFINED ENV{QUL_BUILD_DIR})
message(FATAL_ERROR "QUL_BUILD_DIR not defined!")
endif()
message(STATUS "QUL_BUILD_DIR: $ENV{QUL_BUILD_DIR}")

if(NOT EXISTS ${ProjDirPath}/../platform)
    message(STATUS "platform folder not found! will regenerate platform folder")

    set(QMLPROJECTEXPORTER_EXECUTABLE $ENV{QUL_ROOT}/bin/qmlprojectexporter)
    set(QUL_PLATFORM_METADATA $ENV{QUL_ROOT}/lib/QulPlatformTargets_mimxrt1170-evkb-freertos_32bpp_Linux_armgcc-export.json)
    set(OUTDIR ${ProjDirPath}/../platform)

    set(COMMAND_TO_EXECUTE "${QMLPROJECTEXPORTER_EXECUTABLE}"
                      "--platform-metadata" "${QUL_PLATFORM_METADATA}"
                      "--outdir" "${OUTDIR}"
                      "--project-type" "cmake"
                      "--no-export-qml")
    execute_process(
        COMMAND ${COMMAND_TO_EXECUTE}
        RESULT_VARIABLE RESULT
    )
    if(NOT RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to execute ${COMMAND_TO_EXECUTE}")
    endif()

    file(REMOVE_RECURSE ${OUTDIR}/platform/boards/nxp/mimxrt1170-evkb-freertos/FreeRTOSConfig.h)
else()
    message(STATUS "platform folder found! will load platform folder as source")
endif()

set(SOURCE_DIR 
    ${SOURCE_DIR}
    ${ProjDirPath}/../platform
)

set(STATIC_QUL_LIBS 
    QulCore_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulPlatform_mimxrt1170-evkb-freertos_32bpp_Linux_armgcc_${QUL_LIB_TYPE}
    QulPlatformBSP_mimxrt1170-evkb-freertos_32bpp_Linux_armgcc_${QUL_LIB_TYPE}
    QulControls_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulControlsTemplates_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulDeviceLink_mimxrt1170-evkb-freertos_Linux_armgcc_${QUL_LIB_TYPE}
    QulShapes_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulMonotypeUnicodeEngineShaperDisabled_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulMonotypeFontEngine_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulMonotypeUnicode_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulMonotypeFontEngineAligned_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulMonotypeShaperEngine_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulMonotypeUnicodeEngine_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulWorldTypeSpark_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulITypeSparkAligned_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulITypeSpark_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulPNGDecoderLodePNG_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulPNGDecoderNull_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulProfiling_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulStudioComponents_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
    QulTimeline_cortex-m7-hf-fpv5-d16_Linux_armgcc_${QUL_LIB_TYPE}
)

foreach(QUL_LIB ${STATIC_QUL_LIBS})
    set (STATIC_QUL_LIBS_PATH 
        ${STATIC_QUL_LIBS_PATH}
        $ENV{QUL_BUILD_DIR}/${QUL_LIB_TYPE}/lib${QUL_LIB}.a
    )
endforeach()

