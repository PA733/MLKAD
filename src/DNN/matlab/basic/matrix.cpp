#include "DNN.h"

namespace matlab {
    std::vector<std::vector<double>> matrixMultiply(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
        // Check if the matrices can be multiplied
        if (A[0].size() != B.size()) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        // Create the result matrix
        std::vector<std::vector<double>> C(A.size(), std::vector<double>(B[0].size()));

        // Perform the matrix multiplication
        for (size_t i = 0; i < A.size(); ++i) {
            for (size_t j = 0; j < B[0].size(); ++j) {
                double sum = 0;
                for (size_t k = 0; k < B.size(); ++k) {
                    sum += A[i][k] * B[k][j];
                }
                C[i][j] = sum;
            }
        }
        return C;
    }
    std::vector<double> matrixMultiply(const std::vector<double>& A, const std::vector<std::vector<double>>& B) {
        // Check if the matrices can be multiplied
        if (A.size() != B.size()) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        // Create the result vector
        std::vector<double> C(B[0].size());

        // Perform the matrix multiplication
        for (size_t j = 0; j < B[0].size(); ++j) {
            double sum = 0;
            for (size_t k = 0; k < B.size(); ++k) {
                sum += A[k] * B[k][j];
            }
            C[j] = sum;
        }

        return C;
    }
    std::vector<std::vector<double>> matrixAddition(const std::vector<std::vector<double>>& A, const std::vector<std::vector<double>>& B) {
        // Check if the matrices have the same dimensions
        if (A.size() != B.size() || A[0].size() != B[0].size()) {
            throw std::invalid_argument("Matrix dimensions do not match");
        }

        // Create the result matrix
        std::vector<std::vector<double>> C(A.size(), std::vector<double>(A[0].size()));

        // Perform the matrix addition
        for (size_t i = 0; i < A.size(); ++i) {
            for (size_t j = 0; j < A[0].size(); ++j) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }

        return C;
    }
    std::vector<double> matrixAddition(const std::vector<double>& A, const std::vector<double>& B) {
		// Check if the matrices have the same dimensions
        if (A.size() != B.size()) {
			throw std::invalid_argument("Matrix dimensions do not match");
		}

		// Create the result vector
		std::vector<double> C(A.size());

		// Perform the matrix addition
        for (size_t i = 0; i < A.size(); ++i) {
			C[i] = A[i] + B[i];
		}

		return C;
	}
}