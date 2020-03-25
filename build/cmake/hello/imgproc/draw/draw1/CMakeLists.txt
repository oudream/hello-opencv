
set(gsl_imgproc_draw1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/draw/draw1 "${gsl_imgproc_draw1_files}" gsl_imgproc_draw1_files_filepaths)

add_executable(imgproc_draw1
        ${gsl_imgproc_draw1_files_filepaths}
        )

mc_target_link_libraries(imgproc_draw1)
mc_target_link_opencv(imgproc_draw1)
