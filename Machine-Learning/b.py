import math
def z(x, y):
	return 1.0 - math.exp(-(x ** 4 + (y+3) ** 2))

if __name__ == '__main__':
	delta_z = 10.0
	alpha = 0.01
	x = 10.0
	y = 10.0
	nvz = 0.0
	while (delta_z > 0.0001):
		vz = z(x,y)
		x = x - (alpha * 4 * x ** 3 * math.exp(-x ** 4 - (y+3) ** 2))
		y = y - (alpha * 2 * (y + 3) * math.exp(-x ** 4 - (y+3) **2 ))
		nvz = z(x,y)
		delta_z =  vz - nvz
		print(delta_z)
	print(x, y, nvz, delta_z)