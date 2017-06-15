def main():
	n=int(input())#>=2
	s=input().replace(' ', '')
	
	jumps=0
	i=0
	
	while i < n-3:#step size is 2 and jumps to inclusive last, not end
	
		if s[i+2]=='1':#cant land on these
			i+=3
			jumps+=2#step 1, then 2. small optimization
		else:
			i+=2
			jumps+=1
			
	if i < n-1:#if not on target position
		jumps+=1
		
	print(jumps)

main()