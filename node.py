#!/usr/bin/python

class Node:
	"""Klasa reprezentuje wierzcholek (wezel) grafu"""

	def __init__(self, data):
		self.data = data
		self.neighbours = list()

	def add_neighbour(self, other):
		"""Funkcja dodaje nowy wezel do listy sasiadow"""
		if not isinstance(other, Node):
			raise Exception("Zly typ argumentu")
		self.neighbours.append(other)

	def get_neighbour(self, i):
		"""Funkcja zwraca i-tego sasiada z listy sasiedztwa"""
		if i < 0 or i >= len(self.neighbours):
			raise Exception("Zly indeks")
		return self.neighbours[i]

	def __str__(self):
		return "Node(" + str(self.data) + ")"


import unittest
class TestNode(unittest.TestCase):

	def setUp(self):
		self.wezel = Node(6)

	def test_init(self):
		self.assertEqual(self.wezel.data, 6)
		self.assertEqual(len(self.wezel.neighbours), 0)

	def test_add_neighbour(self):
		self.assertRaises(Exception, self.wezel.add_neighbour, 4)

	def test_add_get_neighbour(self):
		neighbour = Node(11)
		secondNeighbour = Node(9)
		self.wezel.add_neighbour(neighbour)
		self.wezel.add_neighbour(secondNeighbour)
		gN = self.wezel.get_neighbour(0)
		self.assertEqual(gN.data, 11)	
		
	def test_str(self):
		self.assertEqual(self.wezel.__str__(), "Node(6)")

	def tearDown(self): pass

if __name__ == '__main__':
    unittest.main()

