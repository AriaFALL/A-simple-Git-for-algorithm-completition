x=input()
s = "I love python"
print(s.split())
y="Ictfdit"
if x.find("o")!=-1 :
    if len(x)<=10 :
        print(f"{x:*>10}")
    else :
        for i in range (0,10) :
            print(x[i],end="")
else :
    print(f"{y:->10}")

