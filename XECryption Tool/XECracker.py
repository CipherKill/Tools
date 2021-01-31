import sys
#don't judge, i just simply made one quickly
if(len(sys.argv)):
    fname=str(sys.argv[1])
    fkey=str(sys.argv[2])
    searchterm='NULL'
    if('--filename' in fname):
        filename=fname[(fname.index('=')+1):]
    if('--key' in fkey):
        key=fkey[(fkey.index('=')+1):]
        if(key=='?'):
            fsearch=str(sys.argv[3])
            if('--search' in fsearch):
                searchterm=fsearch[(fsearch.index('=')+1):]
else:
    print("No argument provided!")
    input("press enter key...")
    exit()    

file=open(filename,'r')
data=file.read()
data=list(map(int,data.replace('\n','').split('.')))
length=int(len(data))
wordlength=int(length/3)
offset_=key
offset=[ord(i) for i in offset_]
offset=sum(offset)
print("\nXECryption algorithm by cipherKill")
print("\nLETTERS: ",wordlength)
#print("Data: ",data)
print("KEY: ",key)
print("KEYSUM: ",offset)
result=''

try:
    if(key=='?'):
        print("SEARCH TERM: ",searchterm)
        iterations=int(1000000000000)
        print("\nBrute Forcing in progress...")
        for o in range(0,iterations):
            result=''
            for i in range(0,length,3):
                #print('offset= {}, i={}'.format(o,i))
                main_sum=data[i]+data[i+1]+data[i+2]
                #print("calc ",main_sum-offset)
                real_val=chr(abs(main_sum-o))
                result=result+str(real_val)
            if(searchterm in result):
                break
    else:
        print("SEARCH TERM:")
        print("\nFOUND:")
        for i in range(0,length,3):
            main_sum=data[i]+data[i+1]+data[i+2]
            #print("calc ",main_sum-offset)
            real_val=chr(abs(main_sum-offset))
            result=result+str(real_val)
except:
    print("[!]Error : FAULTY KEY ",key)
    print("{}\n".format(result))
if(searchterm=='NULL'):
    None
elif(searchterm in result):
    print("STATUS: Match found!\n")
else:
    print("STATUS: No match found!")
    

print("-----------------------------------\n{}\n-----------------------------------\n".format(result))
