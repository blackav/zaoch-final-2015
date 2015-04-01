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
    for query in cell_recolor_queries:
        cell_colors[query.index] = query.color
        segments_count_responses.append(computeSegmentsCount(cell_colors))
    return segments_count_responses


def computeSegmentsCount(cell_colors):
    return sum(1 for previous, next in zip(cell_colors, cell_colors[1:]) if previous != next) + 1


run()
