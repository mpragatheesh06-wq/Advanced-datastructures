
class SimpleHashTable:
    def __init__(self, table_size):
        self.size = table_size
        self.table = [[] for _ in range(self.size)]

    def my_hash_function(self, key):
        return hash(key) % self.size

    def add_data(self, key, value):
        index = self.my_hash_function(key)
        for pair in self.table[index]:
            if pair[0] == key:
                pair[1] = value  
                return
        
        self.table[index].append([key, value])
        print(f"Added {key} at index {index}")

    def find_value(self, key):
        index = self.my_hash_function(key)
        
        for pair in self.table[index]:
            if pair[0] == key:
                return pair[1]
        
        return "Not Found!"

    def remove_item(self, key):
        index = self.my_hash_function(key)
        
        for i in range(len(self.table[index])):
            if self.table[index][i][0] == key:
                self.table[index].pop(i) 
                print(f"Removed {key} from index {index}")
                return True
        
        return False

    def display(self):
        print("\n--- Current Hash Table State ---")
        for i in range(self.size):
            print(f"Bucket {i}: {self.table[i]}\n")
        


my_ht = SimpleHashTable(5) 

my_ht.add_data("Apple", 10)
my_ht.add_data("Banana", 20)
my_ht.add_data("Cherry", 30) 

my_ht.display()

print(f"Searching for Apple: {my_ht.find_value('Apple')}")

my_ht.remove_item("Apple")
my_ht.display()