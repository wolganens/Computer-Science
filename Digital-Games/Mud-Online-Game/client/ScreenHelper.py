import sys
import os
import re
import json

class ScreenHelper(object):	
	command = ""
	arguments = ""
	options = dict()
	selected = None	
	response = ""
	commands = dict({
		"room" : "Exibe a sala atual",
		"move <n(north), s(south), e(east), w(weast)>" : "Move o personagem para a direção desejada",
		"get_item <nome do item>" : "Pega um item do mapa e coloca no inventário",
		"inventory" : "Exibe os itens do inventário",
		"npc <nome do npc>" : "Interage com um npc",
		"equip <nome do item>" : "Equipa um item do inventário",
		"attack <nome do monstro>" : "Inicia uma batalha com um monstro",
		"me": "Informações do seu personagem",
		"player_info <nome do jogador>": "Informações sobre um jogador online",
		"exit" : "Sai do jogo"
	})
	def __init__(self):
		super(ScreenHelper, self).__init__()
	
	def press_enter(self):
		print("\nEscolha uma opção e pressione ENTER:\n")

	def set_options(self, options):
		self.selected = None
		self.options = options
		self.display_options()


	# Tela inicial do jogo
	def start_screen(self):
		print ("Seja bem-vindo!\n")
		self.command = "start "
		self.set_options({
			"1" : ("1) Já possuo uma conta", 'signin'),
			"2" : ("2) Criar uma conta", 'signup'),
			"3" : ("3) help (Lista de comandos)", 'help')
		})
		self.change_screen(self.options[self.selected][1])

	def help(self):
		print("Lista de comandos:\n")
		for command in self.commands:
			print("{}: {}\n".format(command, self.commands[command]))
		print("Pressione uma tecla para continuar")
		input()
		self.change_screen("start_screen")

	def change_screen(self, screen, alert = None):
		self.clear_screen()
		if alert:
			print(alert)
		getattr(self, screen)()

	def display_options(self):
		# Enquanto a opção selecionada não for válida mostra as opções
		while self.selected not in self.options.keys():
			for value in self.options.values():
				print("{}\n".format(value[0]))
			self.selected = input()
		self.command += self.selected		

	def signup(self):
		self.command = "signup"
		print(
			"Escolha um nome de usuário e uma senha separados por espaço\n"
			"Exemplo: jogadormud umasenhaqualquer"
		)
		user_password = input()
		user_password = user_password.split()
		
		if len(user_password) < 2:
			return self.change_screen(
				"signup",
				"Por favor verifique os dados inseridos!\n"
			)

		self.arguments = "{} {}".format(user_password[0], user_password[1])
	
	def signin(self):
		self.command = "signin"
		print(
			"Digite seu nome de usuário seguido da sua senha separados por espaço\n"
			"Exemplo: joaodasilva minhasenha123"
		)
		user_password = input()
		user_password = user_password.split()
		
		if len(user_password) < 2:
			return self.change_screen(
				"signin",
				"Por favor verifique os dados inseridos!\n"
			)

		self.arguments += "{} {}".format(user_password[0], user_password[1])		
	
	def character_create(self):
		self.command = "character_create"
		print(
			"Agora vamos criar seu personagem.\n"
			"Escolha um nome para o seu personagem e pressione ENTER\n"
			"Exemplo: Prologomena"
		)
		name = input()

		self.arguments = name
	
	def game_start(self):
		self.command = "player_command"
		self.arguments = ""
		while not self.arguments and not self.arguments.strip():
			self.clear_screen()
			print("Digite um comando e pressione ENTER: ")
			self.arguments = input()
		
	def character_description(self):
		self.command = "character_description"
		print(
			"Descreva o seu personagem com um pequeno texto:\n"
			"Exemplo: Um guerreiro nórdico com 2 machados e uma cicatriz "
		)
		description = input()

		self.arguments = description
	def clear_screen(self):
		os.system('cls' if os.name == 'nt' else 'clear')

	def process_response(self):		
		getattr(self,  "{}_response_process".format(self.command))()

	def signup_response_process(self):
		if self.response == 'False':			
			return self.change_screen(
				"signup",
				"Dados inválidos ou o nome de usuário escolhido já existe!\n"
			)
		elif self.response == 'True':
			return self.change_screen(
				"character_create"
			)
		else:
			return print("Resposta inesperada")			
	def character_create_response_process(self):
		if self.response == '1':
			return self.change_screen(
				"character_description"
			)
	def character_description_response_process(self):
		if self.response:
			print("Parabéns! {} seu personagem foi criado com sucesso.".format(self.response))
		print("Pressione ENTER para continuar")
		input()
		return self.change_screen(
			"game_start"
		)
	def player_command_response_process(self):
		if re.match("^{", self.response):			
			self.arguments = ""
			self.display_json_response()			
			while not self.arguments and not self.arguments.strip():
				self.display_json_response()
			return
		elif self.response == '0':
			print("Comando inexistente\nPressione ENTER para continuar:")
			self.arguments = ""
			input()
		else:
			print("Comando: {}\n".format(self.arguments))
			print("Resposta: {}\n".format(self.response))
			print("Pressione ENTER para continuar:\n")
			input()
		return self.change_screen(
			"game_start"
		)
	def signin_response_process(self):
		if self.response == '0':
			return self.change_screen(
				"signin",
				"Dados inválidos, tente novamente!"
			)
		else:
			print("Bem-vindo de volta {} pressione ENTER para continuar!".format(self.response))
			input()
			return self.change_screen(
				"game_start"
			)
	def display_json_response(self):		
		data = json.loads(self.response)		
		print("Name: {}\nDescrição: {}\n".format(data["name"], data["description"]))
		print("Opções:\n")
		for option in data["options"]:
			print("\t{}) {}\n".format(option, data["options"][option]))
		print("\t{}) Cancelar\n".format( len(data["options"]) + 1))
		print("Escolha uma opção:\n")
		self.command = "player_command"
		self.arguments = input()
		if int(self.arguments) > len(data["options"]):
			self.change_screen(
				"game_start"
			)
