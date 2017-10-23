#Repeated String
#https://www.hackerrank.com/challenges/repeated-string
#
#Given a string s, print a single integer denoting
#the number of letter a's in the first k letters of
#the infinite string created by repeating s infinitely many times.

def main():
	str=input().strip()
	k=int(input())
	
	if len(str)>=k:
		print(str.count('a', 0, k))
	else:
		nwhole=k//len(str)#integer division
		rem=k%len(str)
		
		cbefore=str.count('a', 0, rem)
		ctotal = cbefore + str.count('a', rem, len(str))
		
		print(ctotal*nwhole + cbefore)

main()