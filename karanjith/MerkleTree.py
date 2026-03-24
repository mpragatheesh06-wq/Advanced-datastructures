import hashlib
from typing import List

class MerkleNode:
    def __init__(self, left, right, hash_val, content=None):
        self.left = left
        self.right = right
        self.hash = hash_val
        self.content = content

class MerkleTree:
    def __init__(self, data: List[str]):
        self.leaves = [MerkleNode(None, None, self.hash_data(val), val) for val in data]
        self.root = self.build_tree(self.leaves)

    def hash_data(self, data: str) -> str:
        return hashlib.sha256(data.encode('utf-8')).hexdigest()

    def build_tree(self, nodes: List[MerkleNode]) -> MerkleNode:
        if not nodes:
            return None
        if len(nodes) == 1:
            return nodes[0]
            
        parent_level = []
        for i in range(0, len(nodes), 2):
            left = nodes[i]
            right = nodes[i + 1] if i + 1 < len(nodes) else left
            combined_hash = self.hash_data(left.hash + right.hash)
            parent = MerkleNode(left, right, combined_hash)
            parent_level.append(parent)
            
        return self.build_tree(parent_level)

    def get_root_hash(self):
        return self.root.hash if self.root else None

if __name__ == "__main__":
    data_blocks = ["block1", "block2", "block3", "block4"]
    tree = MerkleTree(data_blocks)
    print(f"Merkle Root Hash: {tree.get_root_hash()}")
