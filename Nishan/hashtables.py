class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        return hash(key) % self.size

    def insert(self, key, value):
        index = self.hash_function(key)

        for item in self.table[index]:
            if item[0] == key:
                item[1] = value
                return
        self.table[index].append([key, value])

    def search(self, key):
        index = self.hash_function(key)

        for item in self.table[index]:
            if item[0] == key:
                return item[1]

        return None

    def delete(self, key):
        index = self.hash_function(key)

        for i in range(len(self.table[index])):
            if self.table[index][i][0] == key:
                del self.table[index][i]
                return True

        return False

ht = HashTable(5)

ht.insert("Apple", 10)
ht.insert("Banana", 20)

print("Apple:", ht.search("Apple"))
ht.delete("Apple")
print("Apple after delete:", ht.search("Apple"))
