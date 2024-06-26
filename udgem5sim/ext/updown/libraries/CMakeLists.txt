if (UPDOWNRT_ENABLE_LIBRARIES)
    add_custom_target(libraries)

    set(UPDOWN_RUNTIME_INSTALL_DIR "updown")
    set(UPDOWNSIMRT_LIBRARY_SRC 
        # SpMalloc/testSpMalloc.cpp
    )

    set(UPDOWNSIMRT_PYTHON_LIBRARY_SRC2BIN
        #SpMalloc/testSpMallocEFA.py
        # SpMalloc/spmalloc_test_exe.py
    )

    set(UPDOWN_RUNTIME_LIBRARY_INSTALL_PATH "${UPDOWN_RUNTIME_INSTALL_DIR}/libraries")

    set(UPDOWNSIMRT_PYTHON_LIBRARY_SRC
        UDMapShuffleReduce/Macro.py
        UDMapShuffleReduce/GlobalSync.py
        UDMapShuffleReduce/KeyValueSetTPL.py
        UDMapShuffleReduce/KVMapShuffleReduceTPL.py
        UDMapShuffleReduce/KVMSRMachineConfig.py
        UDMapShuffleReduce/ScratchpadCache.py
        SpMalloc/SpMalloc.py
        SpMalloc/testSpMallocEFA.py
        dramalloc/dramalloc.py
        # ScalableHashTable/sht.py
        # ScalableHashTable/sht_bucket.py
        # ScalableHashTable/memzero.py
        # ScalableHashTable/sht_macros.py
        # ScalableHashTable/sht_confsz.py
        # ScalableHashTable/sht_bucket_confsz.py
        # ScalableHashTable/sht_ext.py
        # ScalableHashTable/sht_lane_ext.py
        # ScalableHashTable/memcpy.py
        # ParallelGraphAbstraction/pga.py
        # ScalableHashTable/sht_call_macros.py
        # ScalableHashTable/sht_confsz_call_macros.py
        # Shmem/LibShmemEFA.py
        # Shmem/UDShmem.py
        Shmem/LibCAUDShmem.py
        Shmem/LibCAUDShmemHPE.py
        Shmem/LibCAUDShmemW3rdPartyMovers.py
        Shmem/CAUDShmem.py
        Shmem/Utils.py
    )

    if(UPDOWN_ENABLE_FASTSIM)
        set(DEPS UDLibs UpDownBASimRuntimeStatic UpDownSimRuntimeStatic m)
    elseif(UPDOWN_ENABLE_ASST)
        set(DEPS UpDownBASimRuntimeStatic UpDownSimRuntimeStatic LaneElements ISAElements m rt)
    else ()
        include_directories(${GEM5_BASE_DIR}/include/)
        link_directories(${GEM5_BASE_DIR}/util/m5/build/x86/out)
        set(DEPS UDLibs UpDownBASimRuntimeStatic UpDownSimRuntimeStatic LaneElements ISAElements m rt m5)
        # set(DEPS UpDownBASimRuntimeStatic UpDownSimRuntimeStatic LaneElements ISAElements m rt m5)
    endif ()

    foreach (LIBRARY_SRC ${UPDOWNSIMRT_LIBRARY_SRC})
        get_filename_component(BARENAME ${LIBRARY_SRC} NAME)
        string(REGEX REPLACE "[.]cpp$" "" LIBRARY_NAME ${BARENAME})
        add_executable(${LIBRARY_NAME} ${LIBRARY_SRC})
        target_link_libraries(${LIBRARY_NAME} ${DEPS})

        INSTALL(TARGETS ${LIBRARY_NAME}
            RUNTIME DESTINATION ${UPDOWN_RUNTIME_LIBRARY_INSTALL_PATH}
        )
    endforeach()

    if(UPDOWN_ENABLE_BASIM)
        set(assem_prog "efa2bin.py")
        foreach(PYFILE IN LISTS UPDOWNSIMRT_PYTHON_LIBRARY_SRC2BIN)
            get_filename_component(PYFILEPATH ${PYFILE} REALPATH) 
            string(REGEX REPLACE "[.]py$" ".bin" PYBIN ${PYFILE})
	    get_filename_component(PYBINFILE ${PYBIN} NAME)
            add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PYBINFILE}
                               COMMAND ${PYTHON_EXECUTABLE} ${assem_prog}
                               ARGS --efa ${PYFILEPATH} --outpath ${CMAKE_CURRENT_BINARY_DIR} --toplinker
                               WORKING_DIRECTORY ${UPDOWN_ASSEMBLER}
                               DEPENDS ${PYFILEPATH})
            list(APPEND UPDOWNSIMRT_PYTHON_UBENCH_BIN ${CMAKE_CURRENT_BINARY_DIR}/${PYBINFILE})
        endforeach()
        add_custom_target(UpdownSimRuntimePythonBin ALL DEPENDS ${UPDOWNSIMRT_PYTHON_UBENCH_BIN})
    endif()

    INSTALL(FILES ${UPDOWNSIMRT_PYTHON_LIBRARY_SRC} DESTINATION ${UPDOWN_RUNTIME_LIBRARY_INSTALL_PATH})
    INSTALL(FILES ${UPDOWNSIMRT_PYTHON_UBENCH_BIN} DESTINATION ${UPDOWN_RUNTIME_LIBRARY_INSTALL_PATH})
    if (UPDOWN_ENABLE_FASTSIM)
        add_library(UDLibs dramalloc/dramalloc_service_core.cpp dramalloc/dramalloc.hpp)
    else ()
       add_library(UDLibs dramalloc/dramalloc_service_core.cpp dramalloc/dramalloc.hpp)
    endif()
endif(UPDOWNRT_ENABLE_LIBRARIES)
