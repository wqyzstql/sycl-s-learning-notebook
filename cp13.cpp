#include <iostream>
#include <sycl/sycl.hpp>
using namespace sycl;

int main(){
    queue q;
    const int M = 4;
    const int N = 4;
    q.submit([&](handler &cgh) {
        stream out(1024,256,cgh);
        cgh.parallel_for(range<2>(M,M), [=](id<2> idx) {
            out << "Testing my sycl stream (this is work-item ID:"<< idx << ")\n";
        });
    });
    buffer<int> in_buf{N}, out_buf{N};
    // Use host accessors to initialize the data
{
    host_accessor in_acc{in_buf}, out_acc{out_buf};
    for (int i = 0; i < N; i++) {
        in_acc[i] = i;
        out_acc[i] = 0;
    }
} // buffer and host_accessor both needs this bracket to declarate scope
    q.submit([&](handler& h) {
        accessor in{in_buf, h};
        accessor out{out_buf, h};
        h.parallel_for(range{N},
        [=](id<1> idx) { out[idx] = in[idx]; });
    });
    // Check that all outputs match expected value
    // Use host accessor! Buffer is still in scope / alive
    host_accessor A{out_buf};
    for (int i = 0; i < N; i++)
    std::cout << "A[" << i << "]=" << A[i] << "\n";

    return 0;
}
