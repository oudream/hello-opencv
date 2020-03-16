
set(gsl_rcnn_rcnn1_files
    mask_rcnn.cpp
        )

mc_merge_file_path(${gs_hello_path}/rcnn/rcnn1 "${gsl_rcnn_rcnn1_files}" gsl_rcnn_rcnn1_files_filepaths)

add_executable(rcnn_rcnn1
        ${gsl_rcnn_rcnn1_files_filepaths}
        )

mc_target_link_libraries(rcnn_rcnn1)
mc_target_link_opencv(rcnn_rcnn1)
