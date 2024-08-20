#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

int main(){
    queue q;
    const int M = 4;
    marray<float, 4> input{1.0004f, 1e-4f, 1.4f, 14.0f};
    marray<float, 4> res[M];
    for (int i = 0; i < M; i++)
        res[i] = {-(i + 1), -(i + 1), -(i + 1), -(i + 1)};

    buffer in_buf(&input, range{1});
    buffer re_buf(res, range{M}); // must have range

    q.submit([&](handler &cgh) {
        accessor re_acc{re_buf, cgh, read_write};
        accessor in_acc{in_buf, cgh, read_only};
        cgh.parallel_for(range<1>(M), [=](id<1> idx) {
            int i = idx[0];
            re_acc[i] = cos(in_acc[0]);
        });
    });

    host_accessor re_acc(re_buf, read_only);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < 4; j++) {
            res[i][j] = re_acc[i][j];
            std::cout << res[i][j] << " ";
        }
        std::cout << '\n';
    }

    return 0;
}
