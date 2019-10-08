// main.cpp

#include <iostream>
#include <vector>
#include "my_algorithm.h"
#include <string>
#include <list>
#include <deque>
#include <list>
#include <sys/time.h>
#include <unistd.h>
#include "get_time.h"  // for get_time()

int main()
{
    using namespace std;
    
    auto beg = get_time();
    
    vector<int> v1 = {4,1111,238,2536,1564,1245,7863,4863,9421,2584,3691,2458,1256,7852};

    auto end = get_time();

    cout << "time: " <<  end - beg    << " us " <<  endl;


    
    for (auto it: v1 )
        cout << it << " ";
    cout << endl;

   
        
    
    insert_sort(v1.begin(),v1.end()); 
    
    
    
    for (auto it: v1 )
        cout << it << " ";
    cout << endl;
  

    return 0;
}
