class bloomin:
    def __init__(self, x):
        self.table = [0 for _ in range(x)] 

    def insert(self, index):
        self.table[index] = 1

    def hash(self, key):
        return (key+(2**key)+67) % len(self.table)
    
    def check(self, key):
        index = self.hash(key)
        return self.table[index] == 1
    

if __name__ == "__main__":
    b = bloomin(20)
    i= int(input("enter number of elements to insert: "))     
    for _ in range(i):
            print(f"enter number {b.table}")
            num = int(input())
            b.insert(b.hash(num))
    
    print("check number")
    num = int(input())
    if b.check(num):
        print("probably in set")
    else:
        print("definitely not in set")