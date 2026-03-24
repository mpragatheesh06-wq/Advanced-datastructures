class HashTable:
    def __init__(self, size):
  
        self.size = size
        
     
        self.table = [[] for _ in range(size)]

    def _hash(self, key):
       
       
        return hash(key) % self.size

    def insert(self, key, value):
       
       
        index = self._hash(key)

       
            if pair[0] == key:
                pair[1] = value   
                return

      

    def search(self, key):
       
        index = self._hash(key)

        for pair in self.table[index]:
            if pair[0] == key:
                return pair[1]

        

    def delete(self, key):
    
        index = self._hash(key)

        for i, pair in enumerate(self.table[index]):
            if pair[0] == key:
                del self.table[index][i]
                return True

   

ht = HashTable(5)

ht.insert("Apple", 10)
ht.insert("Banana", 20)

print("Search 'Apple':", ht.search("Apple"))  

ht.delete("Apple")

print("Search 'Apple' after delete:", ht.search("Apple"))