from Character import Character	
import json
from copy import deepcopy

class Npc(Character):
	def __init__(self, name, description):
		self.name = name
		self.description = description

class NpcShop(Npc):	
	def __init__(self, name, description):
		self.items = list()
		Npc.__init__(self, name, description)

	def get_npc_response(self):
		attributes = deepcopy(vars(self))
		attributes["options"] = dict()
		del attributes["items"]
		for item in self.items:
			attributes["options"][item.id] = item.name
		return json.dumps(attributes)
	def find_item_by_id(self, item_id):
		for item in self.items:            
			if str(item.id) == str(item_id):
				return item
		return False

class NpcQuest(Npc):	
	def __init__(self, name, description, quest = int()):
		self.quest = quest
		Npc.__init__(self, name, description)

	def get_npc_response(self):
		pass
		
		
