
set(gsl_imgproc_draw2_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/draw/draw2 "${gsl_imgproc_draw2_files}" gsl_imgproc_draw2_files_filepaths)

add_executable(imgproc_draw2
        ${gsl_imgproc_draw2_files_filepaths}
        )

mc_target_link_libraries(imgproc_draw2)
mc_target_link_opencv(imgproc_draw2)
