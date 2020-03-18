
// Get a matrix with non-zero values at points where the
// two matrices have different values
cv::Mat diff = a != b;
// Equal if no elements disagree
bool eq = cv::countNonZero(diff) == 0;
