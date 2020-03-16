

### pythoncall2
set(gsl_cxpy_files
        cxpy_module.cpp
        cxpy_noddy2.h
        cxpy_noddy2.cpp
        )

mc_merge_file_path(${gs_hello_path}/python/pythoncall2 "${gsl_cxpy_files}" gsl_noddy_files_filepaths)

add_library(pythoncall2 SHARED
        ${gsl_noddy_files_filepaths}
        )

target_link_libraries(pythoncall2
        ${PYTHON_LIBRARIES}
        )

#compile static
mc_build_with_cc_static()
