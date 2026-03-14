from typing import List
import random

class Node:
    def __init__(self, val, isLeaf, topLeft, topRight, bottomLeft, bottomRight):
        self.val = val
        self.isLeaf = isLeaf
        self.topLeft = topLeft
        self.topRight = topRight
        self.bottomLeft = bottomLeft
        self.bottomRight = bottomRight


class Solution:
    def construct(self, grid: List[List[int]]) -> 'Node':
        
        #           row , col and the number of cells
        def build( r, c , n ):
            
            # To check whether everything is the same
            first_value = grid[r][c]
            isAllSame = True
            for i in range(r , r+n):
                for j in range(c , c+n):
                    if grid[i][j] != first_value:
                        isAllSame = False
            
            # Returns a leaf node
            if isAllSame:
                return Node(val=first_value , isLeaf=True, topLeft=None , topRight=None , bottomLeft=None , bottomRight=None)
            
            # build child nodes...
            split_size = n//2 
            return Node(
                val = first_value,
                isLeaf = False,
                topLeft = build( r, c , split_size ),
                topRight = build( r , c+split_size , split_size),
                bottomLeft = build( r+split_size , c , split_size),
                bottomRight = build( r+split_size , c+split_size , split_size)
            )
        
        #  First call
        return build( 0, 0, len(grid[0])) 
