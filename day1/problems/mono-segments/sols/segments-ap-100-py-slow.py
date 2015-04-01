from __future__ import print_function
from copy import copy
from sys import stdin, stdout


class CellRecolorQuery:
    def __init__(self, index, color):
        self.index = index
        self.color = color


def run():
    cell_colors = readCellColors()
    cell_recolor_queries = readCellRecolorQueries()
    
    printSegmentsCountResponses(
        processCellRecolorQueries(
            cell_colors,
            cell_recolor_queries
        )
    )
    
    
def readCellColors(input_file = stdin):
    cells_count = int(input_file.readline().strip())
    return list(map(int, input_file.readline().split()))


def readCellRecolorQueries(input_file = stdin):
    queries_count = int(input_file.readline().strip())
    return list(map(
        lambda index_color: CellRecolorQuery(index_color[0] - 1, index_color[1]),
        map(
            lambda query_index: tuple(map(int, input_file.readline().split())),
            range(queries_count)
        )
    ))


def printSegmentsCountResponses(segments_count_responses, output_file = stdout):
    print(*segments_count_responses, sep = '\n', end = '', file = output_file)    
    
    
def processCellRecolorQueries(cell_colors, cell_recolor_queries):
    segments_count_responses = []
    segments_count = computeSegmentsCount(cell_colors)
    for query in cell_recolor_queries:
        neighborhood_segments_count_before = computeNeighborhoodSegmentsCount(cell_colors, query.index)
        cell_colors[query.index] = query.color
        neighborhood_segments_count_after = computeNeighborhoodSegmentsCount(cell_colors, query.index)
        segments_count += neighborhood_segments_count_after - neighborhood_segments_count_before
        segments_count_responses.append(segments_count)
    return segments_count_responses


def computeNeighborhoodSegmentsCount(cell_colors, base_index):
    return (
        1
        + (base_index > 0 and cell_colors[base_index] != cell_colors[base_index - 1])
        + (base_index < len(cell_colors) - 1 and cell_colors[base_index] != cell_colors[base_index + 1])
    )


def computeSegmentsCount(cell_colors):
    segments_count = 0
    for cell_index in range(len(cell_colors)):
        if cell_index == 0 or cell_colors[cell_index] != cell_colors[cell_index - 1]:
            segments_count += 1
    return segments_count


run()
