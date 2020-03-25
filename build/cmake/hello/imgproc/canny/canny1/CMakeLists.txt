
set(gsl_imgproc_canny1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/canny/canny1 "${gsl_imgproc_canny1_files}" gsl_imgproc_canny1_files_filepaths)

add_executable(imgproc_canny1
        ${gsl_imgproc_canny1_files_filepaths}
        )

mc_target_link_libraries(imgproc_canny1)
mc_target_link_opencv(imgproc_canny1)
