import json
from pathlib import Path 
from Room import Room
from Item import Item
from Weapon import Weapon
from NPC import Npc, NpcShop, NpcQuest
from Monster import Monster

class World(object):
	# Arquivos json contendo as salas e o mundo composto por elas
	rooms_json_path = Path('./', 'server', 'config', 'rooms', 'rooms.json')
	world_json_path = Path('./', 'server', 'config', 'rooms', 'world.json')
	items_json_path = Path('./', 'server', 'config', 'items', 'items.json')
	npcs_json_path 	= Path('./', 'server', 'config', 'characters', 'npcs.json')
	monsters_json_path 	= Path('./', 'server', 'config', 'characters', 'monsters.json')
	# Dicionário com as saídas de cada sala
	exits = dict()
	# Instancias das salas
	rooms = dict()
	# Dict com todos os itens
	items = dict()
	# Dict com todos os monstros
	monsters = dict()
	# Identificador da sala em que novos jogadores irão aparecer
	default_room_id = "1"

	# Dicionário de direções para o comando move (ex: move:n) ir para o norte
	directions = {
		'n': 0,
		's': 1,
		'e': 2,
		'w': 3
	}
	def __init__(self):
		print("Inicializando o mundo do jogo....\n")
		self.load_items()
		self.load_monsters()
		self.load_npcs()
		self.load_rooms()
		self.load_exits()
	def load_items(self):
		print("Carregando lista de itens...\n")
		with self.items_json_path.open('r') as f:
			items_json_str = f.read()
			self.items = json.loads(items_json_str)
	def load_monsters(self):
		print("Carregando lista de monstros...\n")
		with self.monsters_json_path.open('r') as f:
			monster_json_str = f.read()
			self.monsters = json.loads(monster_json_str)	
	def load_exits(self):
		print("Carregando portais entre as salas...\n")
		with self.world_json_path.open('r') as f:
			world_json_str = f.read()
			self.exits = json.loads(world_json_str)
	
	def load_rooms(self):
		print("Carregando salas...\n")
		with self.rooms_json_path.open('r') as f:
			# Le o arquivo de configuração que contém a lista de salas
			rooms_json_str = f.read()
			json_rooms = json.loads(rooms_json_str)

			# Instancia uma sala para cada entrada do json
			for room_id in json_rooms:
				r = Room(
					int(room_id),
					json_rooms[room_id]["name"],
					json_rooms[room_id]["description"],
				)
				room_items = json_rooms[room_id]["items"]				
				# Carrega os itens especificados no json da sala
				r.items = self.get_items_from_ids(room_items)				
				# Carrega os npc's especificados no json da sala
				if "npcs" in json_rooms[room_id]:
					room_npcs = json_rooms[room_id]["npcs"]
					for npc_id in room_npcs:
						if self.json_npcs[npc_id]["type"] == "quest":
							n = NpcQuest(
								name = self.json_npcs[npc_id]["name"],
								description = self.json_npcs[npc_id]["description"]
							)
						elif self.json_npcs[npc_id]["type"] == "shop":
							n = NpcShop(
								name = self.json_npcs[npc_id]["name"],
								description = self.json_npcs[npc_id]["description"]
							)
							n.items = self.get_items_from_ids(self.json_npcs[npc_id]["items"])
						r.add_npc(n)
				if "monsters" in json_rooms[room_id]:
					room_monsters = json_rooms[room_id]["monsters"]
					for monster_id in room_monsters:
						m = Monster(
							name = self.monsters[monster_id]["name"],
							description = self.monsters[monster_id]["description"],
							hp = self.monsters[monster_id]["hp"],
							damage = self.monsters[monster_id]["damage"],
							drops = self.monsters[monster_id]["drops"],
							exp = self.monsters[monster_id]["exp"],
						)
						r.add_monster(m)
				self.rooms[room_id] = r

	def load_npcs(self):
		print("Carregando NPC's\n")
		# Carrega os npc's do jogo em um dicionário		
		with self.npcs_json_path.open('r') as f:
			npcs_json_str = f.read()			
			self.json_npcs = json.loads(npcs_json_str)

	# Dada uma lista de ids de itens, instancia os mesmos e retorna a lista
	def get_items_from_ids(self, ids):
		items = list()
		for item_id in ids:
			if self.items[item_id]["type"] == "weapon":
				i = Weapon(
					int(item_id),
					self.items[item_id]["name"],
					self.items[item_id]["description"],
					self.items[item_id]["value"],
					self.items[item_id]["damage"],
					self.items[item_id]["type"],
				)
			else:
				i = Item(
					int(item_id),
					self.items[item_id]["name"],
					self.items[item_id]["description"],
					self.items[item_id]["value"],							
					self.items[item_id]["type"],
				)
			items.append(i)
		return items
