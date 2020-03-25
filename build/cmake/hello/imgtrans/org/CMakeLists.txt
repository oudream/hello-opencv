
set(gsl_imgtrans_org_files
#CannyDetector_Demo.cpp
#copyMakeBorder_demo.cpp
#filter2D_demo.cpp
#Geometric_Transforms_Demo.cpp
#HoughCircle_Demo.cpp
#houghcircles.cpp
houghlines.cpp
#HoughLines_Demo.cpp
#imageSegmentation.cpp
#Laplace_Demo.cpp
#Remap_Demo.cpp
#Sobel_Demo.cpp
        )

mc_merge_file_path(${gs_hello_path}/imgtrans/org "${gsl_imgtrans_org_files}" gsl_imgtrans_org_files_filepaths)

add_executable(imgtrans_org
        ${gsl_imgtrans_org_files_filepaths}
        )

mc_target_link_libraries(imgtrans_org)
mc_target_link_opencv(imgtrans_org)
