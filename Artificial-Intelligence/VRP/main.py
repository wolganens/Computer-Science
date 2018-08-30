from Problem import Problem
import Input
import math


def main():
	# Instancia os veículos do problema com a capacidade lida da entrada
	v_capacity, consumers, weights, warehouse = Input.get_input()
	n_vehicles = math.ceil(sum(w for w in weights)/v_capacity)	

	# Cria uma instancia do problema
	p = Problem(n_vehicles, consumers, weights, v_capacity, warehouse)

	# Cria uma solução inicial onde os veículos atendem aglomerados de consumidores
	p.get_initial_solution()

if __name__ == '__main__':
	main()