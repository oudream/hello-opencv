
set(gsl_dnn_rcnn1_files
    mask_rcnn.cpp
        )

mc_merge_file_path(${gs_hello_path}/dnn/rcnn1 "${gsl_dnn_rcnn1_files}" gsl_dnn_rcnn1_files_filepaths)

add_executable(dnn_rcnn1
        ${gsl_dnn_rcnn1_files_filepaths}
        )

mc_target_link_libraries(dnn_rcnn1)
mc_target_link_opencv(dnn_rcnn1)
