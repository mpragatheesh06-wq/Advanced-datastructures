class BloomFilter:
    def __init__(self, size=10):
        self.size = size
        self.bits = [0] * size

    def hash1(self, item):
        return hash(item) % self.size

    def hash2(self, item):
        return (hash(item) * 3) % self.size

    def add(self, item):
        self.bits[self.hash1(item)] = 1
        self.bits[self.hash2(item)] = 1

    def check(self, item):
        if self.bits[self.hash1(item)] == 1 and self.bits[self.hash2(item)] == 1:
            return "Maybe present"
        else:
            return "Not present"
