n =int(input())
nums=0
res=0
x=[]
for i in range(n) :
    res=int(input().split())
    x.append(res)
    nums=nums+x[i]
print(nums)