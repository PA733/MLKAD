#include "DNN.h"

#include <algorithm>


namespace matlab {
    // 2023.07.30 不再可用，但此方法可能更简洁高效，等待以后重构
    //std::vector<double> bsxfun(const std::string fun, const std::vector<double>& A, const std::vector<double>& B) {
    //    std::vector<double> C;
    //    if (fun == "@plus") {
    //        std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::plus<double>());
    //    }
    //    else if (fun == "@minus") {
    //        std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::minus<double>());
    //    }
    //    else if (fun == "@times") {
    //        std::transform(A.begin(), A.end(), B.begin(), std::back_inserter(C), std::multiplies<double>());
    //    }
    //    else {
    //        // handle other functions
    //    }
    //    return C;
    //}

    std::vector<std::vector<double>> bsxfun(const std::string fun, const std::vector<std::vector<double>>& A, const std::vector<double>& B) {
        int A_rows = A.size();
        int A_cols = A[0].size();
        int B_rows = B.size();
        std::vector<std::vector<double>> C(A_rows, std::vector<double>(A_cols));
        if (fun == "@plus") {
            for (int i = 0; i < A_rows; i++) {
                for (int j = 0; j < A_cols; j++) {
                    C[i][j] = A[i][j] + B[i % B_rows];
                }
            }
        }
        else if (fun == "@minus") {
            for (int i = 0; i < A_rows; i++) {
                for (int j = 0; j < A_cols; j++) {
                    C[i][j] = A[i][j] - B[i % B_rows];
                }
            }
        }
        else if (fun == "@times") {
            for (int i = 0; i < A_rows; i++) {
                for (int j = 0; j < A_cols; j++) {
                    C[i][j] = A[i][j] * B[i % B_rows];
                }
            }
        }
        else {
            // handle other functions
        }
        return C;
    }

    std::vector<std::vector<double>> bsxfun(const std::string fun, const std::vector<std::vector<double>>& A, const double& B) {
        int A_rows = A.size();
        int A_cols = A[0].size();
        std::vector<std::vector<double>> C(A_rows, std::vector<double>(A_cols));
        if (fun == "@plus") {
            for (int i = 0; i < A_rows; i++) {
                for (int j = 0; j < A_cols; j++) {
                    C[i][j] = A[i][j] + B;
                }
            }
        }
        else {
            // handle other functions
        }
        return C;
    }
}