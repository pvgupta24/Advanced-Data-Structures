import sys
from random import randint

if(len(sys.argv) < 2):
    print(f"Usage: python3 {sys.argv[0]} <no_of_vertices>")
    exit()

v = int(sys.argv[1])
e = v * (v-1)
print(v, (int)(e/2))

for i in range(v):
    for j in range(i+1, v):
        print(i, j, randint(0, 9999))

print(randint(0, v))
