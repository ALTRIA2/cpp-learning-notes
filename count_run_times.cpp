#include <iostream>
#include <chrono>

int Test1(int N){
  for(int i=0; i< N ;++i)
  std::cout<<"Hellos, World"<<std::endl;
  return 0;
  }
  
int main(){
std::cout<<"The Program Start Run."<<std::endl;
auto start=std::chrono::steady_clock::now();  //start record.
int N=0;
std::cout<<"Please input a number."<<std::endl;
std::cin>>N;
Test1(N);

auto end=std::chrono::duration_cast<std::chrono::microseconds>(end - start);  //end record.
std::cout<<"The Program Run Times is : "<<float(duration.count()/1000000.0)<<" Seconds."<<std::endl;
return 0;
}
