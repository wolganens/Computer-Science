from sys import stdin


def get_input():
    consumers = list()
    weights = list()
    # Le a primeira linha do arquivo, contendo o numero de consumidores
    # e a capacidade maxima dos veiculos            
    n, v_capacity = stdin.readline().strip().split()
    
    # A proxima (segunda) linha contem as coordenadas do deposito
    warehouse = stdin.readline().strip().split()    
    warehouse = [int(warehouse[0]), int(warehouse[1])]
    
    # Enquanto houver linhas para ler do arquivo, armazena os dados dos consumidores
    while 1:
        try:
            consumer = stdin.readline()            
            if consumer and consumer.strip():
                c_data = consumer.split()
                consumer = [int(c_data[0]), int(c_data[1])]
                weights.append(int(c_data[2]))
                consumers.append(consumer)
        except KeyboardInterrupt:
            break
        if not consumer:
            break
    return (int(v_capacity), consumers, weights, warehouse)