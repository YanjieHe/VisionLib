#include <iostream>
#include <Eigen/Dense>

typedef Eigen::Matrix<uint8_t, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> Matrix8u;
using namespace std;

int main(int argc, char** argv)
{
	Matrix8u m(2, 2);
	m(0, 0) = 3;
	m(1, 0) = 2;
	m(0, 1) = 4;
	m(1, 1) = m(1, 0) + m(0, 1);
	for (int i = 0; i < m.rows()+1; i++)
	{
		for (int j = 0; j < m.cols(); j++)
		{
			cout << static_cast<int>(m(i, j)) << " ";
		}
		cout << endl;
	}
	cin.get();
	return 0;
}