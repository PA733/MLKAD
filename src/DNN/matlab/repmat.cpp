#include "DNN.h"

namespace matlab {
	std::vector<std::vector<double>> repmat(const std::vector<double>& A, const int& r) {
		std::vector<std::vector<double>> C;
		for (double i : A) {
			std::vector<double> B;
			for (int j = 0; j < r; j++) {
				B.push_back(i);
			}
			C.push_back(B);
		}
		return C;
	}
	std::vector<double> repmat(const double& A, const int& r) {
		std::vector<double> C;
		for (int j = 0; j < r; j++) {
			C.push_back(A);
		}
		return C;
	}
}