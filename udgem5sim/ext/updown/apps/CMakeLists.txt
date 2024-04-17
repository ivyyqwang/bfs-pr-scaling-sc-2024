include(CMakePrintHelpers)

if (UPDOWNRT_ENABLE_APPS)

    set(UPDOWN_RUNTIME_INSTALL_DIR "updown")

    set(GEM5_DEPS m5 rt)

    set(UPDOWNSIMRT_APPS_SRC 
        pagerank_udkvmsr/pagerankMapShuffleReduce.cpp
        pagerank_udkvmsr/dataLocPagerankMapShuffleReduce.cpp
        pagerank_udkvmsr/preprocess_pagerank.cpp
        pagerank_udkvmsr/pagerankBaseline.cpp

        bfs/updown_bfs.cpp
        bfs/reference_bfs.cpp
        bfs/bfs_baseline.cpp
        bfs/updown_bfs_push_pull.cpp
    )
    if (UPDOWN_ENABLE_FASTSIM)
        list(APPEND UPDOWNSIMRT_APPS_SRC 
        )
    endif()

    include_directories(
        common/glib-adv
        common/glib-core
        common/snap-adv
        common/snap-core
        common/snap-exp
        ../libraries/dramalloc
    )

    set(UPDOWNSIMRT_PYTHON_APPS_SRC
        pagerank_udkvmsr/pr_vertex_split.py

        bfs/bfs_vertex_split.py
        bfs/RMAT.py
    )

    set(UPDOWNSIMRT_PYTHON_APPS_SRC2BIN
        pagerank_udkvmsr/PagerankMsrEFA.py

        bfs/out/bfs_exe.py
        bfs/out/push_pull_exe.py
    )


    set(UPDOWN_RUNTIME_APPS_INSTALL_PATH "${UPDOWN_RUNTIME_INSTALL_DIR}/apps")

    if(UPDOWN_ENABLE_BASIM)
        set(assem_prog "efa2bin.py")
        foreach(PYFILE IN LISTS UPDOWNSIMRT_PYTHON_APPS_SRC2BIN)
            get_filename_component(PYFILEPATH ${PYFILE} REALPATH)
            string(REGEX REPLACE "[.]py$" ".bin" PYBIN ${PYFILE})
	    get_filename_component(PYBINFILE ${PYBIN} NAME)
	    #message("OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PYBINFILE}
	    #         COMMAND ${PYTHON_EXECUTABLE} ${assem_prog}
	    #         ARGS --efa ${PYFILEPATH} --outpath ${CMAKE_CURRENT_BINARY_DIR} --toplinker
	    #         WORKING_DIRECTORY ${UPDOWN_ASSEMBLER}
	    #         DEPENDS ${PYFILEPATH}
	    
            add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PYBINFILE}
                               COMMAND ${PYTHON_EXECUTABLE} ${assem_prog}
                               ARGS --efa ${PYFILEPATH} --outpath ${CMAKE_CURRENT_BINARY_DIR} --toplinker
                               WORKING_DIRECTORY ${UPDOWN_ASSEMBLER}
                               DEPENDS ${PYFILEPATH})
            list(APPEND UPDOWNSIMRT_PYTHON_APPS_BIN ${CMAKE_CURRENT_BINARY_DIR}/${PYBINFILE})
        endforeach()
        add_custom_target(apps ALL DEPENDS ${UPDOWNSIMRT_PYTHON_APPS_BIN})
        add_dependencies(apps libraries)
    endif()


    if (DEFINED CMAKE_GEM5_BASE)
        list(APPEND CMAKE_MODULE_PATH "../../../include")
        cmake_print_variables(GEM5_BASE_DIR)
        include_directories(${GEM5_BASE_DIR}/include/)
        link_directories(${GEM5_BASE_DIR}/util/m5/build/x86/out)
        set(DEPS UDLibs UpDownBASimRuntimeStatic UpDownSimRuntimeStatic m rt m5)
    else ()
        set(DEPS UDLibs UpDownBASimRuntimeStatic UpDownSimRuntimeStatic m)
    endif ()
    link_directories(../libraries/dramalloc)
    foreach (APPS_SRC ${UPDOWNSIMRT_APPS_SRC})
        get_filename_component(BARENAME ${APPS_SRC} NAME)
        string(REGEX REPLACE "[.]cpp$" "" APPS_NAME ${BARENAME})
        add_executable(${APPS_NAME} ${APPS_SRC} common/snap-core/Snap.o)
        target_link_libraries(${APPS_NAME} ${DEPS} )

        INSTALL(TARGETS ${APPS_NAME}
            RUNTIME DESTINATION ${UPDOWN_RUNTIME_APPS_INSTALL_PATH}
        )
    endforeach()

    INSTALL(FILES ${UPDOWNSIMRT_PYTHON_APPS_SRC} DESTINATION ${UPDOWN_RUNTIME_APPS_INSTALL_PATH})
    INSTALL(FILES ${UPDOWNSIMRT_PYTHON_APPS_BIN} DESTINATION ${UPDOWN_RUNTIME_APPS_INSTALL_PATH})

endif(UPDOWNRT_ENABLE_APPS)
