#include "DNN.h"

struct mapminmax_settings {
    std::vector<double> xoffset = {};
    std::vector<double> gain = {};
    double ymin = 0.0;
};

std::vector<std::vector<double>> mapminmax_apply(const std::vector<std::vector<double>>& X, const mapminmax_settings& settings) {
    std::vector<std::vector<double>> C = {};
    C = matlab::bsxfun("@minus", X, settings.xoffset);
    C = matlab::bsxfun("@times", C, settings.gain);
    C = matlab::bsxfun("@plus", C, settings.ymin);
    return C;
}

std::vector<std::vector<double>> tansigApply(const std::vector<std::vector<double>>& n) {
    // Create the result matrix
    std::vector<std::vector<double>> a(n.size(), std::vector<double>(n[0].size()));

    // Perform the tansig function
    for (size_t i = 0; i < n.size(); ++i) {
        for (size_t j = 0; j < n[0].size(); ++j) {
            a[i][j] = 2.0 / (1.0 + std::exp(-2.0 * n[i][j])) - 1.0;
        }
    }

    return a;
}

std::vector<double> logsigApply(const std::vector<double>& n) {
    // Create the result vector
    std::vector<double> a(n.size());

    // Perform the logsig function
    for (size_t j = 0; j < n.size(); ++j) {
        a[j] = 1.0 / (1.0 + std::exp(-n[j]));
    }

    return a;
}

std::vector<double> DNN(const std::vector<std::vector<double>>& X) {
    // ===== NEURAL NETWORK CONSTANTS =====
    // Input 1
    mapminmax_settings x1_step1;
    x1_step1.xoffset = { 1.233971, 0.013611 };
    x1_step1.gain = { 0.324535026497474, 0.737273643167667 };
    x1_step1.ymin = -1;

    // Layer 1
    std::vector<double> b1 = { 4.5158478164146771405, -3.3532047343906583592, -3.2627391421186286991, -0.016298404192669958823, 0.75898454594721331823, 0.61201506393767968195, 1.3876830110504543292, -2.0497788100456584282, 3.3043285248985605485, 2.8739465791206555423 };
    std::vector<std::vector<double>> IW1_1 = { { -4.3472578680236386717, -0.33462033313806255341}, {0.80730939810318524952, 4.4078514038745755244}, {3.8891673915097473291, 0.6635321168244121548}, {-4.354710399241605856, -2.1911670505878100279}, {-3.041551644794131537, -3.1861001517362690372}, {2.0053308721529332637, -3.9658553532241982431}, {0.83024098746710306429, 4.320021424024438339}, {-3.0798596375007862846, -3.9358362714335011212}, {3.8082898291137707858, -2.4611904753762887665}, {3.476267538364708809, 4.0777375780996347743 } };


    // Layer 2
    double b2 = 0.66673547169560165582;
    std::vector<double> LW2_1 = { 0.86317228917825694623, -0.020704729531879371984, -1.061170009734935249, -1.8212420100741528728, 0.51240371996453226711, -0.68044524161831165809, 0.062822878203601620339, -1.7633107794722893136, -0.44141886173681210703, 0.17869707396900677554 };

    // ===== SIMULATION ========
    // Dimensions
    int Q = X[0].size();
    // Input 1
    std::vector<std::vector<double>> Xp1 = mapminmax_apply(X, x1_step1);
    // Layer 1
    std::vector<std::vector<double>> a1 = tansigApply(matlab::matrixAddition(matlab::repmat(b1, Q), matlab::matrixMultiply(IW1_1, Xp1)));
    // Layer 2
    std::vector<double> a2 = logsigApply(matlab::matrixAddition(matlab::repmat(b2, Q), matlab::matrixMultiply(LW2_1, a1)));
    
    return a2;
}