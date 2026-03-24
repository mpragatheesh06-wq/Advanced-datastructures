class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def _hash(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self._hash(key)
        for item in self.table[index]:
            if item[0] == key:
                item[1] = value
                return
        self.table[index].append([key, value])

    def search(self, key):
        index = self._hash(key)
        for item in self.table[index]:
            if item[0] == key:
                return item[1]
        return None

    def delete(self, key):
        index = self._hash(key)
        for i in range(len(self.table[index])):
            if self.table[index][i][0] == key:
                self.table[index].pop(i)
                return True
        return False


ht = HashTable(5)
ht.insert("Apple", 10)
ht.insert("Banana", 20)

print(ht.search("Apple"))
ht.delete("Apple")
print(ht.search("Apple"))