import hashlib
class BloomFilter:
    def __init__(self, array_size, number_of_hashes):
        self.size = array_size
        self.hash_count = number_of_hashes
        self.bits = [0] * array_size

    def add_item(self, item):
       
        for i in range(self.hash_count):
            hash_result = hashlib.md5(f"{i}{item}".encode()).hexdigest()
            index = int(hash_result, 16) % self.size
            
            self.bits[index] = 1
           

    def check_item(self, item):
        for i in range(self.hash_count):
            hash_result = hashlib.md5(f"{i}{item}".encode()).hexdigest()
            index = int(hash_result, 16) % self.size
            
            if self.bits[index] == 0:
                return False 
        
        return True

my_filter = BloomFilter(20, 3)

my_filter.add_item("Cat")
my_filter.add_item("Dog")

print(f"Is 'Cat' in there? {my_filter.check_item('Cat')}")

print(f"Is 'Bird' in there? {my_filter.check_item('Bird')}")

print(f"Final bit array: {my_filter.bits}")