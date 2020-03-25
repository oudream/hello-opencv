
set(gsl_imgproc_canny2_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/canny/canny2 "${gsl_imgproc_canny2_files}" gsl_imgproc_canny2_files_filepaths)

add_executable(imgproc_canny2
        ${gsl_imgproc_canny2_files_filepaths}
        )

mc_target_link_libraries(imgproc_canny2)
mc_target_link_opencv(imgproc_canny2)
