from pathlib import Path
import pickle

class Account(object):
	username = ""
	password = ""
	file_path = None
	player = None
	def __init__(self):
		super(Account, self).__init__()		

	# Cria uma conta de usuário
	def create(self, username, password):
		file_path = Path('./', 'server', 'accounts', "{}.dat".format(username))

		if not username or not password or self.account_file_exists(file_path):
			return False

		self.username = username
		self.password = password
		self.file_path = file_path
		self.save_file()
		return True
	
	# Atualiza os dados de uma conta de usuário
	def update(self):
		self.password = password
		self.save_file()
	
	# Salva o arquivo de uma conta de usuário
	def save_file(self):
		with open(self.file_path, 'wb') as account_file:
			pickle.dump(self, account_file, pickle.HIGHEST_PROTOCOL)
	# Carrega um arquivo de uma conta de usuário
	def get_file(self):		
		with open(self.file_path, 'rb') as account_file:			
			return pickle.load(account_file)
	# Verifica se uma conta de usuário já existe
	def account_file_exists(self, file_path):		
		return file_path.exists()
	
	def set_player(self, player):
		self.player = player
		return self.save_file()

	def signin(self, username, password):
		self.file_path = file_path = Path('./', 'server', 'accounts', "{}.dat".format(username))
		if not username or not password or not self.account_file_exists(file_path):
			return False
		account_file = self.get_file()
		if account_file.username == username and account_file.password == password:
			return account_file
		return False