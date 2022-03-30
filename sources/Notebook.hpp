#include <string>
#include <stdlib.h>
#include <iostream>
#include <tr1/unordered_map>

#pragma once
#include "Direction.hpp"

using namespace std;

namespace ariel
{

    class Notebook
    {
    private:
        // unordered_map<int, unordered_map<string, int> p> n;
        std::tr1::unordered_map<int, std::tr1::unordered_map<int, std::string>> n;

    public:
        void write(int page, int row, int col, Direction d, string txt);
        string read(int page, int row, int col, Direction d, int length);
        void erase(int page, int row, int col, Direction d, int length);
        void show(int page);
    };
}