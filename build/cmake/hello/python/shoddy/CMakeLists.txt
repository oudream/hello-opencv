
### shoddy
set(gsl_shoddy_files
        shoddy1.h
        shoddy1.cpp
        shoddy_config.hpp
        shoddy_module.cpp
        )
mc_merge_file_path(${gs_hello_path}/python/shoddy "${gsl_shoddy_files}" gsl_shoddy_files_filepaths)

add_library(shoddy SHARED
        ${gsl_shoddy_files_filepaths}
        )

target_link_libraries(shoddy
        ${PYTHON_LIBRARIES}
        )

mc_target_link_libraries(shoddy)

#compile static
mc_build_with_cc_static()
