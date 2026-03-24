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


class QuadTree:
    def construct(self, grid: List[List[int]]) -> 'Node':
        
        #          row , col and the number of cells
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
    
def print_tree(node, indent=0):
    if node is None:
        return
    prefix = "  " * indent
    if node.isLeaf:
        print(f"{prefix}Leaf(val={node.val})")
    else:
        print(f"{prefix}Internal")
        print(f"{prefix}  TL:", end=" "); print_tree(node.topLeft, indent+2)
        print(f"{prefix}  TR:", end=" "); print_tree(node.topRight, indent+2)
        print(f"{prefix}  BL:", end=" "); print_tree(node.bottomLeft, indent+2)
        print(f"{prefix}  BR:", end=" "); print_tree(node.bottomRight, indent+2)

def print_grid(size , theMatrix:List[List[int]]):
    print("The Grid :")
    for row in range(size):
        for col in range(size):
            print( theGrid[row][col] , end="")

            if ( col+1 ) % 2 == 0:
                print(" | " , end=" ")
            
        print()
        if ( row+1 ) % 2 == 0:
            print(" - "*size )

# Change this to create/generate random different QuadTrees of different sizes
# USE ONLY POWER OF 2
size = 16
theGrid = [[ random.randint(0,1) for _ in range(size)] for _ in range(size)]

res = QuadTree().construct(theGrid) 

print()
print_grid(size=size , theMatrix=theGrid)
# print_tree(res)
