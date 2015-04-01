/*
 *  Arguments:
 *  cells_count - number of cells
 *  max_color - max absolute value of color
 *  init_segments_count - number of segments to throw initially
 *  init_segments_max_length - max length of these segments
 *  queries_count - number of queries
 *  max_color_cells_count - number of cells with max color value
 */

#include "testlib.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::min;
using std::max;

int s2i(const string &s)
{
    std::stringstream ss;
    ss << s;
    int x;
    ss >> x;
    return x;
}

int main(int argc, char **argv)
{
    registerGen(argc, argv, 1);

    int cells_count = s2i(argv[1]);
    int max_color = s2i(argv[2]);
    int init_segments_count = s2i(argv[3]);
    int init_segments_max_length = s2i(argv[4]);
    int queries_count = s2i(argv[5]);
    int max_color_cells_count = (argc < 7 ? 0 : s2i(argv[6]));

    vector<int> cell_colors(cells_count);
    for (int i = 0; i < cells_count; ++i) {
        cell_colors[i] = rnd.next(-max_color, +max_color);
    }

    for (int i = 0; i < init_segments_count; ++i) {
        int segment_length = rnd.next(1, init_segments_max_length);
        int segment_position = rnd.next(0, cells_count - segment_length);
        std::fill(cell_colors.begin() + segment_position, cell_colors.begin() + segment_position + segment_length - 1, rnd.next(-max_color, +max_color));
    }

    for (int i = 0; i < max_color_cells_count; ++i) {
        cell_colors[rnd.next(cells_count)] = (
            rnd.next(2)
            ? -max_color
            : +max_color
        );
    }

    cout << cells_count << endl;
    for (int i = 0; i < cells_count; ++i) {
        cout << cell_colors[i] << (i == cells_count - 1 ? "\n" : " ");
    }

    cout << queries_count << endl;

    for (int query_index = 0; query_index < queries_count; ++query_index) {

        // Border cells are more probable
        int cell_index = rnd.next(-cells_count / 100, cells_count + cells_count / 100);
        cell_index = min(cell_index, cells_count - 1);
        cell_index = max(cell_index, 0);

        vector<int> colors(10);
        for (int i = 0; i < 10; ++i) {
            colors[i] = rnd.next(-max_color, +max_color);
        }
        if (cell_index > 0) {
            colors[0] = colors[1] = colors[2] = cell_colors[cell_index - 1];
        }
        if (cell_index + 1 < cells_count && (cell_colors[cell_index + 1] != cell_colors[cell_index] || cell_colors[cell_index + 1] != colors[0])) {
            colors[3] = colors[4] = colors[5] = cell_colors[cell_index + 1];
        }
        colors[6] = cell_colors[cell_index];

        cell_colors[cell_index] = colors[rnd.next(10)];

        cout << cell_index + 1 << " " << cell_colors[cell_index] << endl;
    }


    return 0;
}
