import sys
from Problem import Problem
import time

def main():
	if len(sys.argv) < 5:
		print('Utilização: python3 {} <linhas> <colunas> <jogador> <n de simbolos para vencer> <config do tabuleiro>'.format(sys.argv[0]))
		sys.exit(-1)

	# Número de linhas
	m = int(sys.argv[1])
	# Número de colunas
	n = int(sys.argv[2])
	# Índice do jogador que irá jogar
	player_index = int(sys.argv[3])
	# Número de símbolos necessários para configurar uma vitória
	symbols_count = int(sys.argv[4])
	# Configuração inicial do tabuleiro, retorna um vetor de inteiros com os valores das entradas
	start_state = [int(pos) for pos in sys.argv[5:]]
	
	# Verifica se o número de elementos do tabuleiro está correto de acordo com o número de linhas e colunas
	if len(start_state) != m * n:
		print('O estado do jogo deve ter {} elementos'.format(m*n))
		sys.exit(-1)
	# Cria instancia do problema e obtém a próxima ação
	p = Problem(m, n , player_index, symbols_count, start_state)
	empties = len(p.get_valid_actions(p.start_state))	
	next_action = p.get_action(p.start_state, symbols_count * 2)	
	# next_action retorna o último estado que foi avaliado, por isso é preciso fazer o caminho inverso
	# até o primeiro estado para recuperar a ação
	# Enquanto o estado tiver uma ação que levou até ele, retrocede
	# ao estado que o gerou	
	if next_action[3] != None : #o elemento na posição 3 é o estado "pai" que gerou aquele estado
		while next_action[3][2]: #o elemento na posição 2 é a ação tomada para chegar a oestado			
			next_action = next_action[3]	
	print(next_action[2])	
	
if __name__ == '__main__':
	main()