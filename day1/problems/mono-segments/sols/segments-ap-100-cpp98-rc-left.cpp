#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

using std::vector;


struct CellRecolorQuery {
    size_t index;
    int color;

    CellRecolorQuery(size_t _index, int _color) : index(_index), color(_color) {}
};


size_t computeSegmentsCount(vector<int> cell_colors) {
    return std::unique(cell_colors.begin(), cell_colors.end()) - cell_colors.begin();
}


template<typename BidirectionalIterator>
size_t computeNeighborhoodSegmentsCount(BidirectionalIterator begin, BidirectionalIterator base, BidirectionalIterator end) {
    BidirectionalIterator next = base;
    ++next;
    BidirectionalIterator prev = base;
    --prev;
    return
        1
        + (*prev != *base)
        + (next != end && *next != *base);
}


vector<size_t> processCellRecolorQueries(vector<int> cell_colors, const vector<CellRecolorQuery> &cell_recolor_queries) {
    vector<size_t> segments_count_responses;
    segments_count_responses.reserve(cell_recolor_queries.size());

    size_t segments_count = computeSegmentsCount(cell_colors);

    for (
        vector<CellRecolorQuery>::const_iterator query_iterator = cell_recolor_queries.begin();
        query_iterator != cell_recolor_queries.end();
        ++query_iterator
    ) {
        const CellRecolorQuery &query = *query_iterator;
        int neighborhood_segments_count_before = computeNeighborhoodSegmentsCount(
            cell_colors.begin(),
            cell_colors.begin() + query.index,
            cell_colors.end()
        );
        cell_colors.at(query.index) = query.color;
        int neighborhood_segments_count_after = computeNeighborhoodSegmentsCount(
            cell_colors.begin(),
            cell_colors.begin() + query.index,
            cell_colors.end()
        );
        segments_count += neighborhood_segments_count_after - neighborhood_segments_count_before;
        segments_count_responses.push_back(segments_count);
    }

    return segments_count_responses;
}


vector<int> readCellColors(std::istream &in_stream = std::cin) {
    size_t cells_count;
    in_stream >> cells_count;

    vector<int> cell_colors;
    cell_colors.reserve(cells_count);

    for (size_t cell_index = 0; cell_index < cells_count; ++cell_index) {
        int color;
        in_stream >> color;

        cell_colors.push_back(color);
    }

    return cell_colors;
}


vector<CellRecolorQuery> readCellRecolorQueries(std::istream &in_stream = std::cin) {
    size_t queries_count;
    in_stream >> queries_count;

    vector<CellRecolorQuery> queries;
    queries.reserve(queries_count);

    for (size_t query_index = 0; query_index < queries_count; ++query_index) {
        size_t cell_index;
        in_stream >> cell_index;
        int cell_new_color;
        in_stream >> cell_new_color;

        queries.push_back(CellRecolorQuery(cell_index - 1, cell_new_color));
    }

    return queries;
}


void printSegmentsCountResponses(const vector<size_t> &segments_count_responses, std::ostream &out_stream = std::cout) {
    std::copy(segments_count_responses.begin(), segments_count_responses.end(), std::ostream_iterator<size_t>(out_stream, "\n"));
}


int main()
{
    std::istream& in_stream = std::cin;
    std::ostream& out_stream = std::cout;

    vector<int> cell_colors = readCellColors(in_stream);
    vector<CellRecolorQuery> cell_recolor_queries = readCellRecolorQueries(in_stream);

    printSegmentsCountResponses(
        processCellRecolorQueries(
            cell_colors,
            cell_recolor_queries
        ),
        out_stream
    );

    return 0;
}
