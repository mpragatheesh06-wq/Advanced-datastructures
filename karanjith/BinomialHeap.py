class Node:
    def __init__(self, key):
        self.key = key
        self.degree = 0
        self.parent = None
        self.child = None
        self.sibling = None

class BinomialHeap:
    def __init__(self):
        self.head = None

    def merge_trees(self, b1, b2):
        if b1.key > b2.key:
            b1, b2 = b2, b1
        b2.parent = b1
        b2.sibling = b1.child
        b1.child = b2
        b1.degree += 1
        return b1

    def union(self, h1, h2):
        if not h1:
            return h2
        if not h2:
            return h1

        head = None
        b1, b2 = h1, h2

        if b1.degree <= b2.degree:
            head = b1
            b1 = b1.sibling
        else:
            head = b2
            b2 = b2.sibling

        tail = head
        while b1 and b2:
            if b1.degree <= b2.degree:
                tail.sibling = b1
                b1 = b1.sibling
            else:
                tail.sibling = b2
                b2 = b2.sibling
            tail = tail.sibling

        if b1:
            tail.sibling = b1
        if b2:
            tail.sibling = b2

        curr = head
        prev = None
        next_node = curr.sibling

        while next_node:
            if curr.degree != next_node.degree or (next_node.sibling and next_node.sibling.degree == curr.degree):
                prev = curr
                curr = next_node
            elif curr.key <= next_node.key:
                curr.sibling = next_node.sibling
                self.merge_trees(curr, next_node)
            else:
                if prev is None:
                    head = next_node
                else:
                    prev.sibling = next_node
                self.merge_trees(next_node, curr)
                curr = next_node
            next_node = curr.sibling

        return head

    def insert(self, key):
        node = Node(key)
        self.head = self.union(self.head, node)

    def get_min(self):
        if not self.head:
            return None
        min_node = self.head
        curr = self.head.sibling
        while curr:
            if curr.key < min_node.key:
                min_node = curr
            curr = curr.sibling
        return min_node.key

if __name__ == "__main__":
    bh = BinomialHeap()
    bh.insert(10)
    bh.insert(20)
    bh.insert(5)
    bh.insert(30)
    print(f"Minimum in Binomial Heap: {bh.get_min()}")
