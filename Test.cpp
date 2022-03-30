#include <string>
#include "Notebook.hpp"
#include "doctest.h"
#include "Direction.hpp"
using namespace std;
using namespace ariel;

TEST_CASE("check the funcutions write and read:")
{

    ariel::Notebook notebook;

    CHECK_NOTHROW(notebook.write(3, 39, 5, Direction::Horizontal, "check"));
    CHECK_NOTHROW(notebook.write(4, 57, 6, Direction::Horizontal, "check"));
    CHECK_NOTHROW(notebook.write(5, 24, 7, Direction::Horizontal, "check"));
    CHECK_NOTHROW(notebook.write(6, 1, 8, Direction::Horizontal, "check"));
    CHECK_THROWS(notebook.write(-2, 4444, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(-2, 1777777, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(-2, 10, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, -10, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 10, -5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(-2, -10, -5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(0, 10, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 0, 5, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(2, 10, 0, Direction::Horizontal, "abcd"));
    CHECK_THROWS(notebook.write(0, 0, 0, Direction::Horizontal, "abcd"));
    CHECK_NOTHROW(notebook.write(18, 44, 10, Direction::Horizontal, "check"));
    CHECK_THROWS(notebook.read(2, 10, 5, Direction::Vertical, 0));
    CHECK_THROWS(notebook.read(2, 10, 5, Direction::Vertical, -3));
    CHECK_THROWS(notebook.read(0, 0, 0, Direction::Vertical, 0));
}
CHECK_NOTHROW(notebook.erase(5, 31, 2, Direction::Horizontal, 3));

TEST_CASE("Check Symbol")
{
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\t"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\n"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, " "));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\n\n\n"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\r"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "_______"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "~~~~~~~~~~"));
    CHECK_THROWS(notebook.write(2, 10, 5, Direction::Horizontal, "\t\t\t\t\t\t\t"));
}
TEST_CASE("Erasing Check")
{

    notebook.write(15, 12, 3, Direction::Horizontal, "abcd");
    notebook.erase(15, 12, 3, Direction::Horizontal, 4);
    CHECK(notebook.read(15, 12, 3, Direction::Horizontal, 3) == "~~~");
    CHECK(notebook.read(15, 9, 3, Direction::Vertical, 3) == "_~_");
}
// the bad cases
TEST_CASE("bad cases:")
{

    ariel::Notebook notebook;

    notebook.write(1, 10, 12, Direction::Horizontal, " ");
    CHECK(notebook.read(1, 10, 12, Direction::Horizontal, 5) == "error");

    notebook.write(32, 36, 1, Direction::Vertical, " ");
    CHECK(notebook.read(32, 36, 1, Direction::Vertical, 9) == "test fail");

    notebook.write(400, 580, 58, Direction::Vertical, " ");
    CHECK(notebook.read(400, 580, 58, Direction::Vertical, 9) == "failed");
}