
def main():
	while 1:
		x = int(input())
		if x == 0:
			break
		n = x//9 + x
		if x % 9 == 0:
			print(n-1, n)
		else:
			print(n)

if __name__ == '__main__':
	main()