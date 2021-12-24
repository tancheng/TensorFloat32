#include <iostream>
#include "../tf32.hpp"

using namespace std;

int main(){
  tf32 x;
  for(x = 1.0f; x < 2.0f; x.data++){
    cout<<x.data<<" "<<x<<endl;
  }
  
  return 0;
}
