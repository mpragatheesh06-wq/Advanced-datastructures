class Node:
    def __init__(self, data):
        self.data = data
        self.left = None
        self.right = None
        self.height = 1 

class AVLTree:
    def get_height(self, node):
        if node is None:
            return 0
        return node.height

    def get_balance_factor(self, node):
        if node is None:
            return 0
        return self.get_height(node.left) - self.get_height(node.right)

    def right_rotate(self, y):
        x = y.left
        temp = x.right

        x.right = y
        y.left = temp

        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))
        x.height = 1 + max(self.get_height(x.left), self.get_height(x.right))

        return x 

    def left_rotate(self, x):
        y = x.right
        temp = y.left

        y.left = x
        x.right = temp

        x.height = 1 + max(self.get_height(x.left), self.get_height(x.right))
        y.height = 1 + max(self.get_height(y.left), self.get_height(y.right))

        return y

    def insert(self, current_node, new_key):
        if current_node is None:
            return Node(new_key)
        
        if new_key < current_node.data:
            current_node.left = self.insert(current_node.left, new_key)
        elif new_key > current_node.data:
            current_node.right = self.insert(current_node.right, new_key)
        else:
            return current_node 

        current_node.height = 1 + max(self.get_height(current_node.left), 
                                      self.get_height(current_node.right))

        balance = self.get_balance_factor(current_node)

        if balance > 1 and new_key < current_node.left.data:
            return self.right_rotate(current_node)

        if balance < -1 and new_key > current_node.right.data:
            return self.left_rotate(current_node)

        if balance > 1 and new_key > current_node.left.data:
            current_node.left = self.left_rotate(current_node.left)
            return self.right_rotate(current_node)

        if balance < -1 and new_key < current_node.right.data:
            current_node.right = self.right_rotate(current_node.right)
            return self.left_rotate(current_node)

        return current_node
    def show_preorder(self, node):
        if node:
            print(node.data, end=" ")
            self.show_preorder(node.left)
            self.show_preorder(node.right)

my_tree = AVLTree()
root_node = None
numbers = [10, 20, 30, 40, 50, 25]

for n in numbers:
    root_node = my_tree.insert(root_node, n)

print("\nFinal Root:", root_node.data)
print("Tree in Pre-Order:")
my_tree.show_preorder(root_node)
print()