import pdb
def mult(A, B):
    length = len(A) + len(B)
    aOff = 0; bOff = 0; index = length - aOff - bOff - 1
    result = [0 for i in range(length)]
    for a in reversed(A):
        bOff = 0
        for b in reversed(B):
            index = length - aOff - bOff - 1
            temp = int(a) * int(b)
            result[index] += temp
            checkOverflow(result)
            bOff+=1
        aOff += 1
    return result
def checkOverflow(L):
    temp = 0
    for i in range(len(L)):
        num = L[len(L) - i - 1]
        num += temp
        if num >= 10:
            temp = num // 10
            num = num % 10
        else:
            temp = 0
        L[len(L) - i - 1] = num
A = "1234"
B = "5678"

print(mult(A, B))
print(1234*5678)
