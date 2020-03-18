
set(gsl_core_math_stat1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/core/math/stat1 "${gsl_core_math_stat1_files}" gsl_core_math_stat1_files_filepaths)

add_executable(core_math_stat1
        ${gsl_core_math_stat1_files_filepaths}
        )

mc_target_link_libraries(core_math_stat1)
mc_target_link_opencv(core_math_stat1)
