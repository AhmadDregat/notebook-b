#include "Notebook.hpp"
#include "Direction.hpp"

#include <iostream>
#include <stdexcept>
using ariel::Direction;
using namespace std;

const int maxKey = 15;
int minKey = 0;
const int rowLen = 100;

namespace ariel
{

    void Notebook::write(int page, int row, int col, Direction d, string txt)
    {
        if (page < 0 || row < 0 || col < 0 || col >= rowLen)
        { // check the scope of the notebook

            throw std::invalid_argument("Can not write outside the scope of the notebook");
        }

        for (int i = 0; i < txt.length(); i++)
        { // check the txt is with valid chars
            if (txt.at((unsigned long)i) < ' ' || txt.at((unsigned long)i) >= '~')
            {
                throw std::invalid_argument("can not write invalid chars");
            }
        }

        if (Direction::Horizontal == d && (unsigned long)txt.length() + (unsigned long)col > rowLen)
        {
            throw std::invalid_argument("Can not write outside the scope of the notebook");
        }

        if (Direction::Vertical == d)
        { // Vertical case
            for (int i = 0; i < txt.length(); i++)
            {
                if (n[page].count(row + i) == 0)
                {
                    for (int j = 0; j < rowLen; j++)
                    {
                        n[page][row + i].push_back('_');
                    }
                }
            }
            for (int i = 0; i < txt.length(); i++)
            {
                if (n[page][row + i].at((unsigned long)col) != '_')
                {
                    throw std::invalid_argument("Can not write where it is already written");
                }
                n[page][row + i].replace((unsigned long)col, 1, txt.substr((unsigned long)i, 1));
            }
        }

        if (Direction::Horizontal == d)
        { // Horizontal case
            if (n[page].count(row) == 0)
            {
                for (int i = 0; i < rowLen; i++)
                {
                    n[page][row].push_back('_');
                }
            }
            for (unsigned long i = 0; i < txt.length(); i++)
            {
                if (n[page][row].at((unsigned long)col + i) != '_')
                {
                    throw std::invalid_argument("Can not write where it is already written");
                }
            }
            n[page][row].replace((unsigned long)col, txt.length(), txt);
        }
    }
    string Notebook::read(int page, int row, int col, Direction d, int length)
    {
        if (Direction::Horizontal == d && length + col > rowLen)
        {
            throw std::invalid_argument("Can not read outside the scope of the notebook");
        }
        if (length < 0 || page < 0 || row < 0 || col < 0 || col >= rowLen)
        {
            throw std::invalid_argument("Can not read outside the scope of the notebook");
        }

        if (Direction::Horizontal == d)
        {
            if (n[page].count(row) == 0)
            {
                string defultStr;
                for (int i = 0; i < length; i++)
                {
                    defultStr.push_back('_');
                }
                return defultStr;
            }
            return n[page][row].substr((unsigned long)col, (unsigned long)length);
        }
        string resStr; // vetical case

        for (int i = 0; i < length; i++)
        {
            if (n[page].count(row + i) != 0)
            {
                resStr += n[page][row + i].at((unsigned long)col);
            }
            else
            {
                resStr += '_';
            }
        }
        return resStr;
    }
    void Notebook::erase(int page, int row, int col, Direction d, int length)
    {
        if (length < 0 || page < 0 || row < 0 || col < 0 || col >= rowLen)
        {
            throw std::invalid_argument("Can not write outside the scope of the notebook");
        }
        if (Direction::Horizontal == d && length + col > rowLen)
        {
            throw std::invalid_argument("Can not write outside the scope of the notebook");
        }

        if (Direction::Vertical == d)
        { // Vertical case

            for (int i = 0; i < length; i++)
            {
                if (n[page].count(row + i) == 0)
                {
                    for (int j = 0; j < rowLen; j++)
                    {
                        n[page][row + i].push_back('_');
                    }
                }
            }
            for (int i = 0; i < length; i++)
            {
                n[page][row + i].replace((unsigned long)col, 1, "~");
            }
        }
        if (Direction::Horizontal == d)
        { // Horizontal case

            if (n[page].count(row) == 0)
            {
                for (int i = 0; i < rowLen; i++)
                {
                    n[page][row].push_back('_');
                }
            }
            for (unsigned long i = 0; i < length; i++)
            {
                n[page][row].replace((unsigned long)col + i, 1, "~");
            }
        }
    }
    void Notebook::show(int page)
    {
        if (page < 0)
        {
            throw invalid_argument("!!Invalid code");
        }
        while (minKey <= maxKey)
        {
            if (n[page].count(minKey) != 0)
            {
                cout << minKey << ':' << n[page][minKey] << endl;
            }
            minKey++;
        }
    }
}