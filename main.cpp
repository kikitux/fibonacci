#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>

using namespace std;
using namespace std::chrono;

// http://www.cs.utexas.edu/users/EWD/transcriptions/EWD06xx/EWD654.html
// http://www.cs.utexas.edu/users/EWD/ewd06xx/EWD654.PDF

// F(2n)    = (2*F(n-1) + F(n) )*F(n)
// F(2n-1)  = F(n-1)^2 + F(n)^2

unsigned long intfibdijkstra(unsigned long n) {
    static std::vector<unsigned long> values = {0,1,1};
    if (n == 0 ) {
        return values[n];
    }
    if (n < values.size() && values[n] != 0 ) {
        return values[n];
    }
    if (values.capacity() < n){
        values.reserve(n);
    }
    if (values.size() < n){
        values.resize(n);
    }
    if (n%2==0){
       unsigned long num = n/2;
       if (values[num-1]==0)
           values.at(num-1)=intfibdijkstra(num-1);
       if (values[num]==0)
           values.at(num)=intfibdijkstra(num);
       return (2*values[num-1]+values[num])*values[num];
    }
    else {
        unsigned long num = (n+1)/2;
        if (values[num-1]==0)
            values.at(num-1)=intfibdijkstra(num-1);
        if (values[num]==0)
            values.at(num)=intfibdijkstra(num);
        return values[num-1]*values[num-1]+values[num]*values[num];
    }
}

unsigned long intfibonacci(unsigned long n) {
    static std::vector<unsigned long> values = {0,1,1};
    if (n < values.size() ) {
        return values[n];
    }
    for (unsigned long loop = values.size(); loop-1 < n ; ++loop){
        values.push_back(values[loop-2] + values[loop-1]);
    }
    return values[n];
}

int main() {
    cout << "\n";
    unsigned int number = 0;
    cout << "Insert a number to calculate funtions ?:";
    cin >> number ;
    cout << "\n";
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    cout << "Fibonacci number of " << number << " is " << intfibonacci(number) << "\n";
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    cout << "Dijkstra Fibonacci number of " << number << " is " << intfibdijkstra(number) << "\n";
    high_resolution_clock::time_point t3 = high_resolution_clock::now();
    cout << "\n";
    auto durationf = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationd = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();
    cout << "\n";
    cout << "duration fibonacci " << durationf << "\n";
    cout << "duration dijkstra " << durationd << "\n";
    cout << "\n";

    return 0;
}
