import random

alphabet = "abcdefghijklmnopqrstuvwxyz" * 12
alphabet = list(alphabet)

SIZE = 1000000

arr = []
for i in range(1000000, 10000000):
	arr.append(i)
random.shuffle(arr)
arr = arr[:SIZE]

for i in range(SIZE):
	random.shuffle(alphabet)
	arr[i] = (arr[i], "".join(alphabet[:12]), "".join(alphabet[12:24]))


f = open("data_2.csv", 'w')
for i in arr:
	f.write(str(i[0]) + ";" + i[1] + ";" + i[2] + '\n')
f.close()