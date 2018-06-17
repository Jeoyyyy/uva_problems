import math

def gcd(a, b):
	while b != 0:
		a, b = b, a%b
	return a
def main():

	while 1:
		n = int(input())
		if n == 0:
			break
		c1, n1 = input().split()
		c1 = int(c1)
		n1 = int(n1)
		c2, n2 = input().split()
		c2 = int(c2)
		n2 = int(n2)

		if n1 > n and n2 > n:
			print('failed')
			continue

		d1 = n1/c1
		d2 = n2/c2
		if d1 < d2:
			c1, c2, n1, n2 = c2, c1, n2, n1

		lcm = n1 * n2 / gcd(n1, n2)
		minm1 = max(0, math.ceil((n - lcm) / n1))

		m1 = math.ceil(n / n1)
		m2 = 0
		while m1*n1 + m2*n2 != n and m1 >= minm1:
			m1 -= 1
			m2 = int((n - m1 * n1) / n2)

		# maxm2 = int((n - m1*n1) / n2)
		if m1 >= minm1:
			if d1 < d2:
				print(m2, m1)
			else:
				print(m1, m2)
		else:
			print('failed')
	return

if __name__ == '__main__':
	main()

