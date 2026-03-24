# hash fn.
def hash1(word):
    total = 0
    for ch in word:
        total += ord(ch)
    return total % SIZE

def hash2(word):
    total = 1
    for ch in word:
        total *= ord(ch)
    return total % SIZE


def add(word):
    bloom[hash1(word)] = 1
    bloom[hash2(word)] = 1


def check(word):
    if bloom[hash1(word)] == 1 and bloom[hash2(word)] == 1:
        print(word, ": May be present")
    else:
        print(word, ": Not present")

#inpuuts

add("Fr")
add("Lol")

print("Bloom Filter:", bloom)

check("Fr")     # present
check("Lol")   # present
check("Bruuh")   # may or may not be present