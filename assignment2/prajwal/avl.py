import random

class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None
        self.height = 1

class AVLTree:
    def __init__(self):
        self.root = None
        print("a new tree created")

    def insert(self, value , node:Node=None ):

        if node is None:       # leaf
            return Node(value)
        
        # print(f"type of left node : {type(node)}")
        
        # if  node is None and not isFirstCall:                         # just a falg to indicate whether this is the first time calling the method
        #     self.root = self.insert(value=value , node=self.root , isFirstCall=True )
        #     return self.root
        
        # if not node:
        #     return Node(value=value)

        if value < node.value:
            node.left = self.insert(value=value , node=node.left )
        elif value > node.value:
            node.right = self.insert(value=value , node=node.right )
        else:
            return node
        
        # updating the height & balance factor after insertion
        # max() - because the tallest is what determines the height of the node 
        node.height = 1 + max( self.getHeight(node.left) , self.getHeight(node.right))
        balanceFactor = self.getBalanceStatus(node)

        # Selecting which rotation to perform   
        if balanceFactor > 1:
            if self.getBalanceStatus(node.left) >=0:
                print("A L-L case has found")            
                return self.rightRot(node) # LL
            else: 
                print("A L-R case has found")
                node.left = self.leftRot(node.left)
                return self.rightRot(node)  # LR 


        if balanceFactor < -1:
            if self.getBalanceStatus(node.right) <= 0: # RR 
                print("A R-R case has found")
                return self.leftRot(node)
            else:                               # RL 
                print("A R-L case has found")
                node.right = self.rightRot(node.right)
                return self.leftRot(node)
            
        return node
            
    # types of rotation :
    #  * Left-Left (LL) -> single Right Rotation
    #       z            y
    #      /            / \
    #     y         => x   z
    #    /
    #   x
    # * Right-Right (RR)  Single Left rotation
    #   z                 y
    #    \               / \ 
    #     y         =>  z   x
    #       \
    #        x    

    #  * Left-Right (LR) -> Perform a single left rotation on the 2nd child -> then single right rotation 
    #       z                     z                 x
    #      /   leftRot(y)        /   rightRot(z)   / \
    #     y         =>          x       =>        y   z
    #       \                  /
    #         x               y
    #  * Right-Left (RL) -> Single rightRot(y) -> Single leftRot(z)
    #         z                z              x
    #          \                \            /  \
    #           y       =>       x       => z    y
    #          /                  \
    #         x                    y


    def rightRot(self , z:Node ):  # A single right rotation 
        print("A right rotation has performed")
        y:Node = z.left
        t = y.right

        # the actual rotation
        y.right = z
        z.left = t 

        # updating the heights - for finding the the actual height after the rotation
        z.height = 1 + max(self.getHeight(z.left) ,self.getHeight(z.right))
        y.height = 1 + max(self.getHeight(y.left) ,self.getHeight(y.right))

        return y

    def leftRot(self , z:Node ): 
        print("A left rotation is being performed")

        y:Node = z.right
        t = y.left

        # the actual Rotation
        y.left = z
        z.right = t

        # updating the height
        z.height = 1 + max( self.getHeight(z.left) , self.getHeight(z.right)) 
        y.height = 1 + max( self.getHeight(y.left) , self.getHeight(y.right)) 

        print("a left rotation has been performed")
    
        return y

    def getHeight(self , node:Node):
        if not node:
            return 0
        else:
            return node.height
    
    def getBalanceStatus(self , node:Node):
        if not node:
            return 0
        balanceFactor = self.getHeight(node.left) - self.getHeight(node.right)
        return balanceFactor
    

    def printDiagram(self):
        if self.root is None:
            print("(empty tree)")
            return

        lines, *_ = self._buildDiagram(self.root)
        for line in lines:
            print(line)


    def _buildDiagram(self, node):
        """
        Returns:
            lines: list of strings (ASCII diagram)
            width: total width of the diagram
            root_pos: horizontal index of the root value
        """

        val = str(node.value)
        val_width = len(val)

        # Leaf node
        if node.left is None and node.right is None:
            return [val], val_width, val_width // 2

        # Only left child
        if node.right is None:
            left_lines, left_width, left_root = self._buildDiagram(node.left)

            first_line = (left_root + 1) * " " + (left_width - left_root - 1) * "_" + val
            second_line = left_root * " " + "/" + (left_width - left_root - 1 + val_width) * " "

            shifted_left = [line + val_width * " " for line in left_lines]

            return (
                [first_line, second_line] + shifted_left,
                left_width + val_width,
                left_width + val_width // 2
            )

        # Only right child
        if node.left is None:
            right_lines, right_width, right_root = self._buildDiagram(node.right)

            first_line = val + right_root * "_" + (right_width - right_root) * " "
            second_line = (val_width + right_root) * " " + "\\" + (right_width - right_root - 1) * " "

            shifted_right = [val_width * " " + line for line in right_lines]

            return (
                [first_line, second_line] + shifted_right,
                right_width + val_width,
                val_width // 2
            )

        # Two children
        left_lines, left_width, left_root = self._buildDiagram(node.left)
        right_lines, right_width, right_root = self._buildDiagram(node.right)

        first_line = (
            (left_root + 1) * " " +
            (left_width - left_root - 1) * "_" +
            val +
            right_root * "_" +
            (right_width - right_root) * " "
        )

        second_line = (
            left_root * " " + "/" +
            (left_width - left_root - 1 + val_width + right_root) * " " +
            "\\" +
            (right_width - right_root - 1) * " "
        )

        # Pad subtrees to same height
        height = max(len(left_lines), len(right_lines))
        left_lines += [" " * left_width] * (height - len(left_lines))
        right_lines += [" " * right_width] * (height - len(right_lines))

        merged_lines = [
            left_lines[i] + val_width * " " + right_lines[i]
            for i in range(height)
        ]

        return (
            [first_line, second_line] + merged_lines,
            left_width + val_width + right_width,
            left_width + val_width // 2
        )

tree0 = AVLTree()


## Edit these variables:
num_of_nodes = 16
node_value_lower_limit = 0
node_value_upper_limit = 500

for i in range(num_of_nodes):
    val = random.randint(node_value_lower_limit,node_value_upper_limit)
    tree0.root = tree0.insert(val, tree0.root)

tree0.printDiagram()
