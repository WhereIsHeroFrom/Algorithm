#include <iostream>

using namespace std;

char nam[ 100 ][ 100 ] = {
"...............................................................................................",
"..#.........................#...........#.........................#............................",
".#...#####...#...........#...#.........#...#####...#...........#...#..............#####...#....",
"#........#...#.....#.....#....#.......#........#...#...........#....#.................#...#....",
"#.......#....#.....#.....#....#.......#.......#....#...........#....#....#####.......#....#....",
"#......#.....#...#####...#....#...#...#......#.....#...#####...#....#...............#.....#....",
"#.....#......#.....#.....#....#.......#.....#......#...........#....#....#####.....#......#....",
"#.....#......#.....#.....#....#.......#.....#......#...........#....#..............#...........",
".#....#......#...........#....#........#....#......#...........#....#..............#......#....",
"..#..........................#..........#..........................#...........................",
"..............................................................................................."
};

int main() {
    for( int i = 0; i < 11; i ++ ) puts(nam[i]);
}

