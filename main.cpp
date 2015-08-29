#include <iostream>
#include <chrono>
#include <vector>
#include <cmath>
#include <cstdint>

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

// from http://pastebin.com/1U2D143s
// https://twitter.com/JSMuellerRoemer/status/637586563346493440

// "the best way to get the right answer on the Internet is not to ask a question, it's to post the wrong answer."
// https://meta.wikimedia.org/wiki/Cunningham%27s_Law

using result_t = uint_fast64_t;
auto mult(result_t (&a)[2][2], result_t const (&b)[2][2]) -> void
{
    result_t t[2][2];
    for(auto row = 0; row < 2; ++row)
    {
        for(auto col_b = 0; col_b < 2; ++col_b)
        {
            auto & out = t[row][col_b];
            out = 0;
            for(auto col_a = 0; col_a < 2; ++col_a)
                out += a[row][col_a] * b[col_a][col_b];
        }
    }
    for(auto row = 0; row < 2; ++row) for(auto col = 0; col < 2; ++col)
            a[row][col] = t[row][col];
}
auto fast_fib(unsigned n) -> result_t
{
    result_t r[2][2] = {
            {1, 0},
            {0, 1}
    };

    result_t a[2][2] = {
            {1, 1},
            {1, 0}
    };
    if(n <= 1) return n;
    n -= 1;
    while(true)
    {
        if(n & 1)
        {
            mult(r, a);
            if(n == 1) break;
        }
        n >>= 1;
        mult(a, a);
    }
    return r[0][0];
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
    cout << "Fast_fib Fibonacci number of " << number << " is " << fast_fib(number) << "\n";
    high_resolution_clock::time_point t4 = high_resolution_clock::now();
    cout << "\n";
    auto durationf = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    auto durationd = std::chrono::duration_cast<std::chrono::microseconds>( t3 - t2 ).count();
    auto durationfb = std::chrono::duration_cast<std::chrono::microseconds>( t4 - t3 ).count();
    cout << "\n";
    cout << "duration fibonacci " << durationf << "\n";
    cout << "duration dijkstra " << durationd << "\n";
    cout << "duration fast_fib " << durationfb << "\n";
    cout << "\n";

    return 0;
}