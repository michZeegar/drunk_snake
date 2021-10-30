#include <iostream>
#include <bitset>
#include <algorithm>
#include "algorithm.h"
#include "snake.h"


int main(){

    Snake s(3,3,3);
    std::vector<VElement> e;
    s.createVElements(e,0.0);
    std::cout<<"#Elelemnts"<<e.size()<<std::endl;
    // std::vector<VElement> v = {{1,1.0},{2,2.0},{3,3.0},{2,3.0}};

    // auto it =std::find(v.begin(),v.end(),VElement(3,2.3));
    // auto it2 =std::find(v.begin(),v.end(),5);

    // if(it!=v.end()){
    //     std::cout<<it->mStateId<<std::endl;
    // }
    // if(it2!=v.end()){
    //     std::cout<<it->mStateId<<std::endl;
    // }else{
    //     std::cout<<"Not in list"<<std::endl;
    // }

    // StateCreator s;
    // std::vector<std::pair<int,int>> b = {{0,1},{0,1},{-1,0}};
    // std::pair<uint8_t,uint8_t> h = {3,1};
    // std::pair<uint8_t,uint8_t> t = {1,1};

    // std::vector<std::pair<int,int>> b2 = {{0,1},{1,0},{0,1},{1,0},{0,-1},{0,-1},{0,-1},{0,-1},{-1,0}};

    // uint64_t x = s.createState(t,h,b);
    // uint64_t y = s.createState(t,h,b2);

    // std::cout<<std::bitset<38>(x)<<std::endl;
    // std::cout<<std::bitset<38>(y)<<std::endl;



    return 0;
}
