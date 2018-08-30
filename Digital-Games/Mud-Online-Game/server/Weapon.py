from Item import Item
class Weapon(Item):
	# Dano causado pela arma
	damage = None

	def __init__(self, item_id, name, description, value, damage, item_type):
		self.damage = damage
		super().__init__(item_id, name, description, value, item_type)
