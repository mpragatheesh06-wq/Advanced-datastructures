import hashlib

class BloomFilter:
    def __init__(self, size, hash_count):
        self.size = size
        self.hash_count = hash_count
        self.bit_array = [0] * size

    def _hashes(self, item):
        result = []
        for i in range(self.hash_count):
            h = hashlib.md5(f"{i}{item}".encode()).hexdigest()
            result.append(int(h, 16) % self.size)
        return result

    def add(self, item):
        for index in self._hashes(item):
            self.bit_array[index] = 1

    def contains(self, item):
        for index in self._hashes(item):
            if self.bit_array[index] == 0:
                return False
        return True


bf = BloomFilter(20, 3)
bf.add("Cat")
bf.add("Dog")

print(bf.contains("Cat"))
print(bf.contains("Bird"))