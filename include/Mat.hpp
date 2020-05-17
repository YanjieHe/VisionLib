#ifndef MAT_HPP
#define MAT_HPP
#include <Eigen/Dense>
#include <memory>
using MatrixUInt8 = Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> ;

class Mat
{
public:
	std::shared_ptr<MatrixUInt8> data;
};

#endif // MAT_HPP