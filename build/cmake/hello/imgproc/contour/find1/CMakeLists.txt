
set(gsl_imgproc_contour_find1_files
        main.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgproc/contour/find1 "${gsl_imgproc_contour_find1_files}" gsl_imgproc_contour_find1_files_filepaths)

add_executable(imgproc_contour_find1
        ${gsl_imgproc_contour_find1_files_filepaths}
        )

mc_target_link_libraries(imgproc_contour_find1)
mc_target_link_opencv(imgproc_contour_find1)
