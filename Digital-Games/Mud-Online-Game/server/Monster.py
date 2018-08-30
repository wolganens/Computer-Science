from Item import Item
from Character import Character

class Monster(Character):
    def __init__(self, name, description, hp, damage, drops, exp):
        self.hp = hp
        self.damage = damage
        self.drops = drops
        self.exp = exp
        Character.__init__(self, name, description)    