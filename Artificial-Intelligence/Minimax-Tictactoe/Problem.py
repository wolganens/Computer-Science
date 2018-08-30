import copy
from numpy import reshape
from time import time

class Problem(object):
	"""Classe principal para o problema do jogo"""
	
	def __init__(self, m, n , player_index, symbols_count, start_state):
		# Número de linhas
		self.m = m
		# Número de colunas
		self.n = n
		self.current_player = player_index
		# Indices dos jogadores
		self.max_player = player_index
		# Define o indice do jogador min
		self.min_player = 2 if player_index == 1 else 1
		# Número de simbolos em sequencia para uma vitória
		self.symbols_count = symbols_count		
		# Profundidade máxima que a busca na árvore pode expandir
		self.max_depth = 10
		# Configuração inicial do "tabuleiro"
		self.format_state(start_state)		

	# Esta função serve para formatar o estado inicial que vem apenas como um vetor
	# com as configurações do tabuleiro
	def format_state(self, start_state):
		# Cria uma matriz para representar o tabuleiro e mapeia os indices
		# do vetor para os indices da matriz		
		board = reshape(start_state, (self.m, self.n)).tolist()
		# board = [[0 for col in range(self.m)] for row in range(self.n)]
		# for i in range(len(start_state)):
		# 	board[int(i / self.m)][i % self.n] = start_state[i]
		# Define o estado inicial do problema:
		# [0] = Utilidade do estado
		# [1] = Configuração do tabuleiro
		# [2] = Ação que gerou o estado
		# [3] = Estado "pai"
		self.start_state = [0, board, None, None]
	
	# Printa no saida do so a configuração do tabuleiro
	def print_state(self, state):
		for i in range(self.m):
			print('-'.join(['-----' for k in range(self.n)]))
			print(' '.join(['| X |' if state[1][i][j] == 1 else '| O |' if state[1][i][j] == 2  else '|   |' for j in range(self.n)]))
		print('-'.join(['-----' for k in range(self.n)]))

	# Conta quantos simbolos em sequencia (na linha) o jogador tem na posição atual
	def get_right_seq(self, state, i, j, player):
		# Qual indice esta na posição atual a ser verificada
		position_symbol = state[1][i][j]
		# Se o simbolo na posicao atual é 0 ou não é o do jogador,
		# então ele não tem nenhuma sequencia a partir dessa posição
		if position_symbol == 0 or position_symbol != player:
			return 0
		# Começa a contar quantos simbolos o jogador tem a partir da posicao atual		
		count = 1
		col = j + 1
		# Enquanto os proximos simbolos forem do jogador e não passar do limite, contabiliza
		# os simbolos
		while col < self.n and state[1][i][col] == player:
			count += 1
			col += 1
		return count
	
	# Conta quantos simbolos em sequencia (na coluna) o jogador tem na posição atual
	def get_bottom_seq(self, state, i, j, player):
		# Qual indice esta na posição atual a ser verificada
		position_symbol = state[1][i][j]
		# Se o simbolo na posicao atual é 0 ou não é o do jogador,
		# então ele não tem nenhuma sequencia a partir dessa posição
		if position_symbol == 0 or position_symbol != player:
			return 0
		# Começa a contar quantos simbolos o jogador tem a partir da posicao atual		
		count = 1
		row = i + 1
		# Enquanto os proximos simbolos forem do jogador e não passar do limite, contabiliza
		# os simbolos
		while row < self.m and state[1][row][j] == player:
			count += 1
			row += 1
		return count

	# Conta quantos simbolos em sequencia (na diagonal da direita) o jogador tem na posição atual
	def get_right_diag_seq(self, state, i, j, player):
		# Qual indice esta na posição atual a ser verificada
		position_symbol = state[1][i][j]
		# Se o simbolo na posicao atual é 0 ou não é o do jogador,
		# então ele não tem nenhuma sequencia a partir dessa posição
		if position_symbol == 0 or position_symbol != player:
			return 0
		# Começa a contar quantos simbolos o jogador tem a partir da posicao atual		
		count = 1
		col = j + 1
		row = i + 1
		# Enquanto os proximos simbolos forem do jogador e não passar do limite, contabiliza
		# os simbolos
		while (row < self.m and col < self.n) and state[1][row][col] == player:
			count += 1
			row += 1
			col += 1
		return count
	
	# Conta quantos simbolos em sequencia (na diagonal da direita) o jogador tem na posição atual
	def get_left_diag_seq(self, state, i, j, player):
		# Qual indice esta na posição atual a ser verificada
		position_symbol = state[1][i][j]
		# Se o simbolo na posicao atual é 0 ou não é o do jogador,
		# então ele não tem nenhuma sequencia a partir dessa posição
		if position_symbol == 0 or position_symbol != player:
			return 0
		# Começa a contar quantos simbolos o jogador tem a partir da posicao atual		
		count = 1
		col = j - 1
		row = i + 1
		# Enquanto os proximos simbolos forem do jogador e não passar do limite, contabiliza
		# os simbolos
		while (row < self.m and col >= 0) and state[1][row][col] == player:
			count += 1
			row += 1
			col -= 1
		return count

	# Determina se um um jogador venceu a partida no estado state
	def is_player_winner(self, state, player):
		# Para cada posição do tabuleiro, a função verifica se o jogador
		# possui uma sequencia de simbolos do tamanho da sequencia necessária para vencer
		for i in range(0, self.m):
			for j in range(0, self.n):
				row_count1 = self.get_right_seq(state, i, j, player)
				if row_count1 == self.symbols_count:
					return True
				
				col_count1 = self.get_bottom_seq(state, i, j, player)
				if col_count1 >= self.symbols_count:
					return True
				
				right_diag_count1 = self.get_right_diag_seq(state, i, j, player)
				if right_diag_count1 == self.symbols_count:
					return True

				left_diag_count1 = self.get_left_diag_seq(state, i, j, player)
				if left_diag_count1 == self.symbols_count:
					return True
		return False
		
	# Determinina se as posições atuais no tabuleiro configuram alguma vitória ou se houve empate
	def terminal_test(self, state):
		# Se não há mais sucessores então é um estado terminal
		if len(self.get_valid_actions(state)) == 0:			
			return True
		# verifica para cada posição do tabuleiro, se qualquer um dos jogadores (1/2),
		# possui uma sequencia de simbolos do tamanho que configura uma vitoria
		for i in range(0, self.m):
			for j in range(0, self.n):
				row_count1 = self.get_right_seq(state, i, j, 1)
				row_count2 = self.get_right_seq(state, i, j, 2)				
				if row_count1 == self.symbols_count or row_count2 == self.symbols_count:					
					return True
				
				col_count1 = self.get_bottom_seq(state, i, j, 1)
				col_count2 = self.get_bottom_seq(state, i, j, 2)
				if col_count1 == self.symbols_count or col_count2 == self.symbols_count:					
					return True
				
				right_diag_count1 = self.get_right_diag_seq(state, i, j, 1)
				right_diag_count2 = self.get_right_diag_seq(state, i, j, 2)
				if right_diag_count1 == self.symbols_count or right_diag_count2 == self.symbols_count:					
					return True

				left_diag_count1 = self.get_left_diag_seq(state, i, j, 1)
				left_diag_count2 = self.get_left_diag_seq(state, i, j, 2)
				if left_diag_count1 == self.symbols_count or left_diag_count2 == self.symbols_count:					
					return True

	# Função heurística para atribuir um valor a um estado em função do número de simbolos
	def h(self, state):		
		# Se o adversário perde, da um valor negativo alto para o estado
		if self.is_player_winner(state, self.max_player):
			return self.symbols_count
		# Se o jogador do turno vence, da um valor positivo ao tabuleiro,
		elif self.is_player_winner(state, self.min_player):
			return -1 * self.symbols_count
		# Se nenhum dos jogadores vence e não há mais jogadas disponíveis, então há um empate, retorna 0
		elif len(self.get_valid_actions(state)) == 0:
			return 0
		else:
			# Se o algoritmo não chegou a nenhum estado terminal, verifica qual dos jogadores tem a maior
			# sequencia de símbolos, e retorna uma pontuação com base no tamanho dessa sequencia
			player_seq_count = list()
			for i in range(0, self.m):
				for j in range(0, self.n):
					player_seq_count.append(self.get_right_seq(state, i, j, self.max_player)),
					player_seq_count.append(self.get_bottom_seq(state, i, j, self.max_player)),
					player_seq_count.append(self.get_right_diag_seq(state, i, j, self.max_player)),
					player_seq_count.append(self.get_left_diag_seq(state, i, j, self.max_player))

					player_seq_count.append(-1 * (self.get_right_seq(state, i, j, self.min_player))),
					player_seq_count.append(-1 * (self.get_bottom_seq(state, i, j, self.min_player))),
					player_seq_count.append(-1 * (self.get_right_diag_seq(state, i, j, self.min_player))),
					player_seq_count.append(-1 * (self.get_left_diag_seq(state, i, j, self.min_player)))
			
			# Retorna a sequencia de maior valor absoluto, tendo em vista que quando é o adversário que estamos
			# avaliando, o resultado é negativo então medimos apenas a magnitude
			return max(player_seq_count, key=lambda x: abs(x))

	# Retorna uma lista de indíces [i,j] cujo valor no tabuleiro é 0
	def get_valid_actions(self, state):
		actions = [[i,j] for i in [i for i in range(self.m)] for j in range(self.n) if state[1][i][j] == 0]		
		return actions
	
	# A partir de uma ação(i,j) substitui a posição pelo indice do jogador e gera o estado
	def get_successor(self, state, action, player):		
		board = copy.deepcopy(state[1])
		i,j = action
		board[i][j] = player		
		state = [0, board, '{} {}'.format(i,j), state]		
		return state
	
	# Retorna a ação a ser tomada com base na configuração atual do tabuleiro
	def get_action(self, state, depth):		
		if len(self.get_valid_actions(state)) == self.m * self.n:
			state[2] = '{} {}'.format(int(self.m / 2), int(self.n / 2))
			return state
		self.start_time = time()		
		alpha = [-99999999]
		beta = [99999999]
		val = self.value(state, depth, alpha, beta, True)
		return val
	
	# Função encarregada de chamar as funções max_value e min_value dependendo de quem é a vez
	def value(self, state, depth, alpha, beta, max_turn):		
		# Avalia o estado no caso da profundidade máxima ser atingida ou o estado ser terminal		
		if self.terminal_test(state) or depth == 0 or (time() - self.start_time >= 900):
			state[0] = self.h(state)			
			return state
		if max_turn:
			return self.max_value(state, depth, alpha, beta)
		else:
			return self.min_value(state, depth, alpha, beta)

	def max_value(self, state, depth, alpha, beta):
		v = [-999999999]
		sucessors = [self.get_successor(state, action, self.max_player) for action in self.get_valid_actions(state)]
		for s in sucessors:
			v = max(v, self.value(s, depth - 1, alpha, beta, False))
			# Faz a poda na arvore
			if v[0] >= beta[0]:
				break
			# Melhor valor que o max pode obter
			alpha = max(alpha, v)
		return v

	def min_value(self, state, depth, alpha, beta):
		v = [999999999]
		sucessors = [self.get_successor(state, action, self.min_player) for action in self.get_valid_actions(state)]
		for s in sucessors:
			v = min(v, self.value(s, depth - 1, alpha, beta, True))
			# Faz a poda na arvore
			if v[0] <= alpha[0]:
				break
			# Melhor valor que o min pode obter
			beta = min(beta, v)
		return v