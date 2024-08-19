#include<sycl/sycl.hpp>
#include<iostream>
#include<vector>

using namespace sycl;

int main(){
    buffer<int> a_buf{range{10}};
    buffer <int, 2> buf{range(10,10)};
    std::vector<std::vector<int> >vec(10,std::vector<int>(10,1));
    buffer v_buf{vec};
    queue q;

    // accessor a_acc{a_buf};
    //
    // q.submit([&](handler &h){
    //     accessor acc(buf,h,write_only);
    //     h.parallel_for(range<2>(10,10),[=](id<2>idx){
    //         acc[idx]=idx[0]+idx[1];
    //     });
    // }).wait();
    // q.submit([&](handler &h){
    //     h.require(a_acc);
    //     h.parallel_for(range<1>(10),[=](id<1>idx){
    //         a_acc[idx]=idx[0];
    //     });
    // }).wait();
    // q.submit([&](handler &h){
    //     accessor v_acc(v_buf, h, write_only);
    //     h.parallel_for(range<2>(10, 10),[=](id<2>idx){
    //         v_acc[idx[0]][idx[1]]=idx[0]+idx[1];
    //     });
    // }).wait();

    host_accessor hacc(v_buf);
    for(int i=0;i<10;i++)   for(int j=0;j<10;j++)
        std::cout<<hacc[i][j]<<" ";


    return 0;
}
