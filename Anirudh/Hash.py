SIZE = 10

#  hash table
hash_table = [[] for _ in range(SIZE)]

# hash fn.
def hash_function(key):
    total = 0
    for ch in key:
        total += ord(ch)
    return total % SIZE

# insert fn.
def insert(key, value):
    index = hash_function(key)
    hash_table[index].append([key, value])

# search fn.
def search(key):
    index = hash_function(key)
    for item in hash_table[index]:
        if item[0] == key:
            print(key, "found with value", item[1])
            return
    print(key, "not found")

# I/P

insert("Milan", 10)
insert("Madrid", 20)
insert("Paris", 30)

print("Hash Table:", hash_table)

search("Madrid")
search("Barca")
