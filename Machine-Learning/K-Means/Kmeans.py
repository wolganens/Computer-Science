import sys
from random import randint
import math

class Kmeans():
	def __init__(self, k, data):
		self.data = data
		self.k = int(k)
		self.centroids = list()
		self.random_start()
	
	def random_start(self):
		for i in range (0, self.k):
			self.centroids.append([randint(-500, 2000), randint(-600, 1400), i])
		print(self.centroids)

	def get_nearest_centroid(self, point):
		distances = []
		for centroid in self.centroids:
			distances.append( math.sqrt(((point[0] - centroid[0]) ** 2) + ((point[1] - centroid[1]) ** 2)) )
		return distances.index(min(distances))

	def update_membership(self):
		membership_updated = False
		
		for point in self.data:
			new_membership = self.get_nearest_centroid(point);
			if point[2] != new_membership:
				membership_updated = True
			point[2] = new_membership;		

		return membership_updated
	def update_centroids(self):		
		for i in range(0, self.k):
			i_points = [point for point in self.data if point[2] == i]
			x_mean = sum([point[0] for point in i_points])/len(i_points)
			y_mean = sum([point[1] for point in i_points])/len(i_points)
			self.centroids[i] = [x_mean, y_mean, i]

def main(n_k):
	data = list()
	with open('data.dat', 'r') as f:
		while True:
			line = f.readline()
			if not line:
				break
			x, y = line.split()
			data.append([float(x), float(y), None])
	k = Kmeans(n_k, data)
	
	while k.update_membership():
		k.update_centroids()

	for i in range(0, n_k):
		for member in [p for p in k.data if p[2] == i]:
			with open('k{}'.format(i), 'a') as f:
				f.write('{} {}'.format(member[0], member[1]))
				f.write('\n')
	

if __name__ == '__main__':
	k = sys.argv[1]
	main(int(k))
		