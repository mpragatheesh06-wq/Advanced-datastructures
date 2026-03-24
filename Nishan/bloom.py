import hashlib

class BloomFilter:
    def __init__(self, size, hash_count):
        self.size = size
        self.hash_count = hash_count
        self.bit_array = [0] * size

    def get_hashes(self, item):
        indexes = []
        for i in range(self.hash_count):
            hash_value = hashlib.md5((str(i) + item).encode()).hexdigest()
            index = int(hash_value, 16) % self.size
            indexes.append(index)
        return indexes

    def add(self, item):
        for index in self.get_hashes(item):
            self.bit_array[index] = 1

    def contains(self, item):
        for index in self.get_hashes(item):
            if self.bit_array[index] == 0:
                return False
        return True

bf = BloomFilter(20, 3)

bf.add("Cat")
bf.add("Dog")

print("Contains 'Cat':", bf.contains("Cat"))
print("Contains 'Bird':", bf.contains("Bird"))
