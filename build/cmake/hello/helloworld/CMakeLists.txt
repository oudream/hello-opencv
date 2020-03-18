
set(gsl_helloworld_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/helloworld "${gsl_helloworld_files}" gsl_helloworld_files_filepaths)

add_executable(helloworld
        ${gsl_helloworld_files_filepaths}
        )

mc_target_link_libraries(helloworld)
mc_target_link_opencv(helloworld)
