class Room(object):		
	def __init__(self, room_id, name, description):
		self.items = list()
		self.npcs = list()
		self.monsters = list()
		self.id = room_id
		self.name = name
		self.description = description

	# Coloca um item na sala
	def add_item(self, item):
		self.items.append(item)
	# Coloca um npc na sala
	def add_npc(self, npc):
		self.npcs.append(npc)
	# Coloca um monstro na sala
	def add_monster(self, monster):
		self.monsters.append(monster)
	# Retorna uma string com os dados gerais da sala
	def get_response_string(self):
		response = ""
		response = "Sala: {}\nDescrição: {}\n".format(self.name, self.description)
		response += "Itens: \n"					
		for item in self.items:
			response += "\t{}\n".format(item.name)
		response += "Npc's:\n"
		for npc in self.npcs:
			response +="\t{}\n".format(npc.name)
		response += "Monstros:\n"
		for monster in self.monsters:
			response +="\t{}\n".format(monster.name)
		return response

	# Encontra (ou não) pelo nome, um item na sala 
	def item_in_room(self, item_name):	
		for item in self.items:
			if item.name == item_name:
				index = self.items.index(item)
				return self.items.pop(index)
		return False

	# Encontra (ou não) um npc na sala pelo seu nome
	def get_npc_by_name(self, npc_name):
		for npc in self.npcs:
			if npc.name == npc_name:
				return npc
		return False

	# Encontra (ou não) um monstro na sala pelo seu nome
	def get_monster_by_name(self, monster_name):
		for monster in self.monsters:
			if monster.name == monster_name:
				return monster
		return False
	
	def remove_monster(self, monster):
		return self.monsters.remove(monster)