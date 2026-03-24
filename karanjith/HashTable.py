class HashTable:
    def init(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hf(self, key):
        return (key + 67) % self.size

    def ik(self, key, value):
        index = self.hf(key)
        space = self.table[index]
        space.append([key, value])
        print("inserted key :-", key)

    def sk(self, key):
        index = self.hf(key)
        space = self.table[index]
        for i in range(len(space)):
            if space[i][0] == key:
                return space[i][1]
        return None

    def dk(self, key):
        index = self.hf(key)
        space = self.table[index]
        for i in range(len(space)):
            if space[i][0] == key:
                del space[i]
                print("key del:-", key)
                return True
        print("not found")
        return False


ht = HashTable()
size = int(input("table size: "))
ht.init(size)

while True:
    print("\n1.insert \n2.search \n3.delete \n4.exit")
    ch = int(input("choice: "))
    if ch == 1:
        k = int(input("key: "))
        v = input("Enter value: ")
        ht.ik(k, v)

    elif ch == 2:
        k = int(input("Enter key to search: "))
        res = ht.sk(k)
        if res is not None:
            print(f"Value: {res}")
        else:
          print("Key not found")

    elif ch == 3:
        k = int(input("Enter key to delete: "))
        ht.dk(k)

    elif ch == 4:
        print("Exit")
        break
    else:
        print("Invalid choice")