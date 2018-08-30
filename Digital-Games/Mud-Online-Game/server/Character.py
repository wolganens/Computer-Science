class Character(object):
	
	def __init__(self, name, description = False):
		self.name = name
		if description:
			self.description = description
	def set_description(self, description):
		self.description = description
	
	def is_alive(self):
		return self.hp > 0

	def attack(self, character):
		if self.damage:
			character.hp -= self.damage