#pragma once

#include <iostream>
#include <vector>

// 创建一个matlab命令空间
namespace matlab
{
	// ==================== 基础运算 ====================
	// matrixMultiply
	std::vector<std::vector<double>> matrixMultiply(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	std::vector<double> matrixMultiply(const std::vector<double>&, const std::vector<std::vector<double>>&);
	// matrixAddition
	std::vector<std::vector<double>> matrixAddition(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	std::vector<double> matrixAddition(const std::vector<double>&, const std::vector<double>&);
	// ==================================================
	// bsxfun
	std::vector<std::vector<double>> bsxfun(const std::string fun, const std::vector<std::vector<double>>&, const std::vector<double>&);
	std::vector<std::vector<double>> bsxfun(const std::string, const std::vector<std::vector<double>>&, const double&);
	//rapmat
	std::vector<std::vector<double>> repmat(const std::vector<double>&, const int&);
	std::vector<double> repmat(const double&, const int&);
}

std::vector<double> DNN(const std::vector<std::vector<double>>&);