from pathlib import Path
from Character import Character
from Room import Room
from Account import Account
import pickle

class Player(Character):
	def __init__(self, name, account):
		self.file_path = Path('./', 'server', 'characters', "{}.dat".format(name))
		self.username = account.username
		self.notifications_buffer = bytes()	
		self.current_room_id = None
		self.username = ""
		self.last_commands = list()
		self.inventory = list()
		self.account = account
		self.weapon = None
		self.hp = 200
		self.damage = 5
		self.level = 0
		self.gold = 0
		Character.__init__(self, name)
	
	def move(self, room):
		try:
			self.set_current_room(room)
			self.account.save_file()
		except Exception as e:
			raise e
	
	def set_current_room(self, room):
		self.current_room_id = room

	def save_file(self):
		with open(self.file_path, 'wb') as character_file:
			pickle.dump(self, character_file, pickle.HIGHEST_PROTOCOL)
	
	def add_item(self, item):
		self.inventory.append(item)
		self.account.save_file()
		return "{} adicionado ao inventário".format(item.name)

	def get_inventory_response(self):
		if len(self.inventory) == 0:
			return "\tInventário vazio"
		
		response = "Inventário\n"
		for item in self.inventory:
			response += ("\t{}\n".format(item.name))
		return response

	def equip_item(self, item_name):		
		for item in self.inventory:
			# Procura o item que o usuário tentou equipar
			if item.name == item_name:
				# Dependendo do tipo do item, equipa no lugar adequado
				if item.__class__.__name__ == "Weapon":
					# Se o jogador já está usando uma arma, coloca ela no inventário
					if self.weapon is not None:
						self.inventory.append(self.weapon)
						self.damage-=self.weapon.damage

					# Tira o item do inventário e coloca no slot de arma equipada
					self.weapon = self.inventory.pop(self.inventory.index(item))
					self.damage += self.weapon.damage
					return "Item equipado com sucesso!"
		return False

	def get_info_response(self):
		response = (
			"Name: {}\n"
			"Descrição: {}\n"
			"Level: {}\n"
			"HP: {}".format(self.name, self.description, self.level, self.hp)
		)
		return response