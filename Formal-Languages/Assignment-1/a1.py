import sys
import re
import ast
import collections
from graphviz import Digraph
import time

class Afd(object):
	"""Classe que representa o automato finito deterministico"""
	def __init__(self, alphabet, states, transitions, start_state, final_states):
		""" Inicializa o automato com seus atributos"""				
		self.alphabet = alphabet
		self.states = states
		self.transitions = transitions
		self.start_state = start_state
		self.final_states = final_states
		self.minimized = False

	#Funcao de transicao extendida definida recursivamente
	def extended(self, state, word):
		if (not word): #base para leitura de palavra vazia retornando o proprio estado
			return state
		else:
			#inducao separando o ultimo caractere da palavra(wa)
			q = state
			w = word[0:len(word)-1]
			a = word[-1]
			return self.transition(self.extended(q,w),a)

	#Verifica a existencia de uma transicao partindo de "state" lendo "symbol"
	def transition(self, state, symbol):
		for transition in self.transitions:
			transition = tuple(transition)
			transition_state, transition_symbol, transition_result_state = transition
			if transition_state == state and transition_symbol == symbol:			
				return transition_result_state
	
	#Verifica se uma palavra "word" eh aceita pelo automato
	def test_word(self, word):
		""" 
			testa se a interseccao resultado da 
			funcao extendida com o conjunto de estados finais 
			eh diferente de conjunto vazio
		"""
		print "\n"
		print "Palavra: " + word		
		if self.extended(self.start_state, word) in self.final_states:
			print 'ACEITA'
		else:
			print 'REJEITADA'
		print "\n"
	
	""" 
		Busca em profundidade para encontrar todos os 
		estados acessiveis a partir de um estado "start"
	"""
	def getReachables(self, start):
		S = []
		visited = []
		S.append(start)
		while len(S) > 0:
			v = S.pop()
			if v not in visited:
				visited.append(v)
				for s in self.getAdjacents(v):
					S.append(s)
		self.reachables = visited
		return self.reachables
	
	#Estados adjacentes de um estado "state"
	def getAdjacents(self, state):
		states = []
		for transition in self.transitions:
			transition = tuple(transition)
			transition_state, transition_symbol, transition_result_state = transition
			if transition_state == state:
				states.append(transition_result_state)
		return states
	
	#Estados inacessiveis do automato
	def get_unreachables(self):
		"""
			Diferenca entre o conjunto de estados do automato
			e o conjunto de estados acessiveis
		"""			
		self.unreachables = self.states.difference(set(self.getReachables(self.start_state)))
		return self.unreachables
	
	#Estados mortos do automato
	def dead_states(self):
		not_final_states = self.states.difference(self.final_states)
		dead_states = set()		
		for state in not_final_states:
			"""
				Se a partir de um estado que nao eh final nao houver transicao
				que leve a um estado final, entao o estado eh mortos
			"""
			if set(self.getReachables(state)).isdisjoint(self.final_states):
				dead_states.add(state)		
		self.dead_states = dead_states

		
		return self.dead_states
		
	#Minimiza o automato - https://en.wikipedia.org/wiki/DFA_minimization
	def minimize(self):		
		self.states = self.states.difference(self.get_unreachables())
		self.states = self.states.difference(self.dead_states())		

		P = set([frozenset(self.final_states),frozenset(self.states.difference(self.final_states))])
		W = set([frozenset(self.final_states)])

		while len(W) > 0:
			A = W.pop()
			for c in self.alphabet:
				X = set()
				for state in self.states:
					for transition in self.transitions:
						if transition[1] == c and transition[2] in A:
							X.add(transition[0])								
				Y = set([y for y in P if len(X.intersection(y)) > 0 and len(y.difference(X)) > 0])								
				for y in Y:
					x_and_y = frozenset(X.intersection(y))
					y_not_x = frozenset(y.difference(X))					
					P.discard(y)
					P.add(x_and_y)
					P.add(y_not_x)
					if y in W:
						W.discard(y)
						W.add(x_and_y)
						W.add(y_not_x)
					else:
						if len(x_and_y) <= len(y_not_x):
							W.add(x_and_y)
						else:
							W.add(y_not_x)
		new_states = list()
		for eq_class in P:
			temp_name = ""
			for state in eq_class:
				temp_name+= state
			new_states.append(temp_name)
		
		self.states =  set(new_states)

		#transicoes sem estados inacessiveis ou mortos
		transitions = [transition for transition in self.transitions if transition[0] not in self.dead_states and transition[2] not in self.unreachables and transition[0] not in self.unreachables and transition[2] not in self.dead_states]
		

		#novas transicoes para os novos estados
		new_transitions = list()
		
		while len(transitions) > 0:
			t = transitions.pop()
			new_t = (self.get_new_state(t[0]),t[1],self.get_new_state(t[2]))
			if new_t not in new_transitions:
				new_transitions.append(new_t)			
		
		self.transitions = new_transitions
		
		self.minimized = True

		#novos estados finais
		states = set()
		for state in self.final_states:
			for s in self.states:
				if state in s:
					states.add(s)
		self.final_states = states

		#novo estado inicial
		self.start_state = self.get_new_state(self.start_state)

	#retorna o novo nome do estado
	def get_new_state(self, s):
		for state in self.states:		
			if s in state:
				return state
	def show_afd_info(self):
		print "\nEstados:"
		print self.states
		print "\nAlfabeto:"
		print self.alphabet
		print "\nTransicoes:"
		print self.transitions
		print "\nEstado inicial:"
		print self.start_state
		print "\nEstados finais"
		print self.final_states
		#EXIBIR MORTOS E INACESSIVEIS
		print "\n"
	def export_graph(self):
		dot = Digraph()
		for state in self.states:
			label = state
			if state in self.final_states:
				label+= " - Final"
			if state == self.start_state:
				label+= " - Inicial"
			dot.node(state, label)

		for transition in self.transitions:
			dot.edge(transition[0],transition[2], transition[1])

		timestr = time.strftime("%Y%m%d-%H%M%S")
		dot.render(timestr)
		print "\nArquivo %s.pdf salvo com sucesso!\n" % timestr

def test(match):
	return "\'" + match.group() + "\'"

	
alphabet = set()
states = set()
transitions = []
start_state = ''
final_states = set()
afd = None

file_name  = sys.argv[1]
f = open(file_name)

p = re.compile(r'[aA0-zZ9]*[^\s\(\),]')
try:
    for line in f:
		regex = r"\({(.*)},{([aA0-zZ9,]*)},{((\([aA0-zZ9,]*\),?)+)},([aA0-zZ9]*),{([aA0-zZ9,]*)}\)"
		test_str = line
		matches = re.finditer(regex, test_str, re.DOTALL)
		for matchNum, match in enumerate(matches):
			alphabet = set(ast.literal_eval('[' + p.sub(test, match.group(1)) + ']'));
			states = set(ast.literal_eval('[' + p.sub(test, match.group(2)) + ']'));
			transitions = ast.literal_eval('[' + p.	sub(test,  match.group(3)) + ']')
			start_state = match.group(5)
			final_states =  set(ast.literal_eval('[' + p.sub(test, match.group(6)) + ']'));
		afd = Afd(alphabet, states, transitions, start_state, final_states)		
finally:
    f.close()

nb = 2
while nb != 1:
	try:		
		nb = int(raw_input('Opcoes do programa:\n1 - Sair\n2 - Minimizar\n3 - Testar palavra \n4 - Exportar automato\n'))
	except Exception as e:
		continue
	if nb == 3:
		word = raw_input('Digite a palavra: ')
		afd.test_word(word)
	elif nb == 2:
		if afd.minimized == True:
			print "O automato ja foi minimizado"
		else:
			afd.minimize()
	elif nb == 4:
		afd.export_graph()