
### noddy
set(gsl_noddy_files
        noddy1.h
        noddy1.cpp
        noddy2.h
        noddy2.cpp
        noddy3.h
        noddy3.cpp
        noddy4.h
        noddy4.cpp
        noddy_config.h
        noddy_config.cpp
        noddy_module.cpp
        )

mc_merge_file_path(${gs_hello_path}/python/noddy "${gsl_noddy_files}" gsl_noddy_files_filepaths)

add_library(noddy SHARED
        ${gsl_noddy_files_filepaths}
        )

target_link_libraries(noddy
        ${PYTHON_LIBRARIES}
        )

mc_target_link_libraries(noddy)

#compile static
mc_build_with_cc_static()
