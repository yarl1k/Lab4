#pragma once
#include <iostream>
#include <chrono>
#include <format> 

using namespace std;

template <class F>
auto timeit(F&& f, int repeat = 1)
{
    auto time1 = chrono::steady_clock::now();
    while (repeat--)
        f();
    auto time2 = chrono::steady_clock::now();
    auto tdiff = time2 - time1;
    return chrono::duration<double>(tdiff).count();
}