Para rodar o servidor:
	python(3 ou >) server/Server.py
Para rodar o cliente
	python(3 ou >) client/Client.py

Arquivos principais:
	server/Server.py
		Classe do servidor multi-thread que trata cada requisição dos jogadores
	client/Client.py
		"Telas" do jogo e troca de mensagens com o servidor
	config/*/*.json
		Arquivos contendo informações carregadas na inicialização do servidor (itens, monstros, salas)
	accounts/*.dat
		Arquivos contendo o estado corrente dos usuários
	server/*.py
		Arquivos das classes de "regra de negócio"(modelos) do jogo

Obs: Como indicado nas primeiras linhas, deve-se usar a versão 3 ou superior do python, o jogo foi criado
com a versão 3.6 instalada nas máquinas

O diretório também contém um ambiente virtual (pacote virtualenv do python), que pode ser ativado pelo comando: source bin/activate, utilizar o ambiente virtual é opcional. INstalamos ele para não mistuar as versões do python do sistema operacional com a mais atualizada (3.6 no momento)

Por enquanto a interação com NPC's funciona apenas com npc's do tipo Shop, NPC de quest ainda não está implementado