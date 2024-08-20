#include <iostream>
#include <mkl.h>

int main() {
    // 定义矩阵 A 的尺寸
    int m = 3, k = 2;

    // 定义矩阵 B 的尺寸
    int n = 4;

    // 创建并初始化矩阵 A 和 B
    float A[] = {
        1, 2,
        3, 4,
        5, 6
    };
    float B[] = {
        1, 3, 5, 7,
        2, 4, 6, 8
    };

    // 结果矩阵 C
    float C[3*4] = {0};

    // Leading dimensions
    int lda = k, ldb = n, ldc = n;

    // 矩阵乘法参数
    float alpha = 1.0f;
    float beta = 0.0f;

    // 调用 cblas_sgemm 进行矩阵乘法
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);

    // 输出结果矩阵 C
    std::cout << "Result Matrix C:" << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << C[i*n + j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
