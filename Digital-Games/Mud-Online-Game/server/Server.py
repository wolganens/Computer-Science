import socket
import threading
import socketserver
from Player import Player
from Account import Account
from World import World
import re
from copy import deepcopy
global commands
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
class Server(object):
  host = "localhost"
  port = 9999
  tcpServer = None
  server_thread = None    
  clients = dict()    
  world = None
  def __init__(self, host, port):
    super(Server, self).__init__()
    self.host = host
    self.port = port
    self.tcpServer = ThreadedTCPServer((self.host, self.port), ThreadedTCPRequestHandler)
    self.world = World()
    self.lock = threading.Lock()
  def start(self):
    with self.tcpServer:
      self.server_thread = threading.Thread(target=self.tcpServer.serve_forever)      
      self.server_thread.daemon = False
      self.server_thread.start()
      print("Servidor iniciado com sucesso na thread:", self.server_thread.name)
      print("Aguardando a conexão de clientes...")
      self.tcpServer.serve_forever()

class ThreadedTCPRequestHandler(socketserver.BaseRequestHandler):
  player = None
  response_buffer = bytes()

  def handle(self):
    global server
    sock = self.request
    socket_descriptor = sock.fileno()

    command = ""
    while command != "exit":
      response = ""
      command = self.receive()
      command_parts = command.split(maxsplit=1)
      if re.match(r"signup", command):
        # Separa as duas partes dos dados: usuário e senha
        username_password = command_parts[1].split()

        # Cria a nova conta com os dados informados
        username = username_password[0]
        password = username_password[1]
        account = Account()
        account_created = account.create(username, password)
        
        # Se a conta foi criada com sucesso, mantem ela em memória na lista de clientes
        if account_created:
          if socket_descriptor not in server.clients:
            server.clients[socket_descriptor] = dict()
            server.clients[socket_descriptor]["socket"] = sock

            self.account = server.clients[socket_descriptor]["account"] = account
            # Verifica se o cliente já está conectado, através do descritor do socket

            response = account_created
      elif re.match(r"signin", command):
        # Separa as duas partes dos dados: usuário e senha
        username_password = command_parts[1].split()

        # Cria a nova conta com os dados informados
        username = username_password[0]
        password = username_password[1]
        
        # Instancia a conta e carrega a última versão do arquivo da conta do jogador
        account = Account()
        account_signedin = account.signin(username, password)

        if account_signedin:
          if socket_descriptor not in server.clients:
            server.clients[socket_descriptor] = dict()
            server.clients[socket_descriptor]["socket"] = sock

          self.account = server.clients[socket_descriptor]["account"] = account_signedin
          self.player = server.clients[socket_descriptor]["player"] = self.account.player
            
          response = self.account.player.name          
        else:
          self.set_response_buffer('0')
      elif re.match(r"character_create", command):
        # Obtem o nome do jogador, enviado pelo cliente, instancia a classe e armazena      
        name = command_parts[1]     
        player = Player(name, self.account)
        
        # Cria uma referência do jogador para facilitar acesso
        
        if player:
          server.clients[socket_descriptor]["player"] = player

          self.player = player
          response = "1"
      elif re.match(r"character_description", command):               
        # Seta a descrição do personagem enviada pelo player
        self.player.set_description(command_parts[1])
        
        # Após criar o personagem por completo, move ele para a sala inicial
        self.player.move(server.world.default_room_id)

        # Adiciona uma referência do player na sua conta
        self.account.set_player(self.player)

        notification = "# {} entrou no jogo! #".format(player.name)
        border = ""
        for i in range(len(notification)):
          border += "#"
          self.broadcast_message(
            "{}\n{}\n{}".format(border, notification, border)                   
            )
          response = player.name
      elif re.match(r"player_command", command):
        # O comando que o jogador inseriu
        arguments = []                
        player_command = command_parts[1]
        splited_player_command = player_command.split()

        if len(splited_player_command) > 1:
          player_command = splited_player_command[0]
          arguments = splited_player_command[1:]

        # Mantem um histórico dos comandos inseridos pelo jogador
        self.player.last_commands.append((player_command, arguments))
        
        # Começa a verificar os comandos existentes
        if player_command == "help":
          global commands
          response += "Lista de comandos:\n"
          for command in commands:
            response += "{}: {}\n".format(command, commands[command])
        elif player_command == "me":
          response += self.player.get_info_response()
        # Informações sobre um jogador
        elif player_command == "player_info":
          if len(arguments) < 1:
            response += "Informe o nome do jogador"
          else:
            player_name = arguments[0]
            found = False
            for client in server.clients:
              if server.clients[client]["player"].name == player_name:
                found = True
                response += server.clients[client]["player"].get_info_response()
            if not found:
              response += "Jogador não encontrado (nome incorreto ou offline)"
        elif player_command == "room":
          # Obtem a sala em que o jogador se encontra e envia     
          room = server.world.rooms[self.player.current_room_id]
          # String descrevendo a sala
          response = room.get_response_string()                   

        elif player_command == "playercount":
          # Envia o número de clientes conectados
          response = "{} jogadores conectados".format(len(server.clients))

        elif player_command == "move":
          # Obtem a direção para onde o player quer se mover
          direction = arguments[0]

          # Se a direção for inválida
          if direction not in server.world.directions:
            response = "Direção inválida!"
          else:
            try:
              # Saidas possíveis para a sala atual
              exits = server.world.exits[self.player.current_room_id]
              # Valor do indíce que a direção representa nas saídas
              direction_index = server.world.directions[direction]                            
              # Nova sala do jogador                          
              self.player.move(exits[direction_index])
              # Envia a descrição da nova sala para o jogador
              room = server.world.rooms[self.player.current_room_id]                          
              response = room.get_response_string()

            except Exception as e:
              print(e)
              response = "Direção inválida!"
        elif player_command == "get_item":
          item_name = arguments[0]
          #Inicio de seção crítica
          server.lock.acquire()   
          item = server.world.rooms[self.player.current_room_id].item_in_room(item_name)
          server.lock.release()
          # Fim de seção crítica                  
          if item is False:
            response = "Item não encontrado"                
          else:                   
            response = self.player.add_item(item)                   

        elif player_command == "inventory":
          response = self.player.get_inventory_response()

        elif player_command == "npc":
          # Se o npc tiver um nome composto, junta os argumentos para compor o nome
          npc_name = " ".join(arguments)
          # Busca a sala do player atual e encontra o npc nela pelo seu nome
          room = server.world.rooms[self.player.current_room_id]
          npc = room.get_npc_by_name(npc_name)

          # Mantem em memória o npc que o usuário está interagindo
          self.interacting_with = ("npc", npc)
          response = npc.get_npc_response()
        elif re.match(r"^\d$", player_command):
          if self.interacting_with[0] == "npc":
            npc = self.interacting_with[1]
          if npc.__class__.__name__ == "NpcShop":                            
            item_id = player_command
            item = npc.find_item_by_id(item_id)
            if item:
              if self.player.gold < item.value:
                response = "Você não tem dinheiro suficiente!"
              else:
                self.player.add_item(deepcopy(item))
                response = "Item comprado com sucesso!"
            else:
              response = "Este item não está a venda no NPC"
        elif player_command == "equip":
          item_name = arguments[0]
          equiped = self.player.equip_item(item_name)
          if not equiped:
            response = "Item não encontrado no seu inventario!"
          else:
            response = equiped
        elif player_command == "attack":
          # Busca um monstro com o nome informado no mapa atual do player
          monster_name = npc_name = " ".join(arguments)
          room = server.world.rooms[self.player.current_room_id]
          monster = room.get_monster_by_name(monster_name)          
          if not monster:
            response = "Monstro não encontrado na sala atual"
          else:
            response += "Batalha iniciada:\n"
            # Enquanto alguem estiver vivo, dalhe pau
            while monster.is_alive() and self.player.is_alive():
              self.player.attack(monster)            
              monster.attack(self.player)

              response += "\tSua hp: {}\n\tHP do monstro:{}\n".format(self.player.hp, monster.hp)

            if not self.player.is_alive():
              response += "\nVocê perdeu a batalha"
            elif not monster.is_alive():
              response += "\nVocê venceu a batalha"
              self.player.inventory += server.world.get_items_from_ids(monster.drops)
              room.remove_monster(monster)
              del monster
        elif player_command == "exit":
          # Quando o jogador sair, remove ele da lista de clientes        
          server.clients[socket_descriptor].pop("socket")
          server.clients[socket_descriptor].pop("player")
          server.clients.pop(socket_descriptor)          
          server.tcpServer.shutdown()
        else:
          response = "0"
      self.set_response_buffer(response)
      try:                
        self.send()
      except Exception as e:
        print(e)
        break

  # Recebe comandos vindos do cliente
  def receive(self):
    return str(self.request.recv(1024), 'utf-8')

  # Envia respostas ao cliente com o conteúdo do seu buffer de resposta
  def send(self):     
    self.request.sendall(self.response_buffer)
    self.response_buffer = bytes()
    if self.player:
      self.player.notifications_buffer = bytes()

  # Envia uma mensagem para todos os jogadores conectados
  def broadcast_message(self, message):
    global server
    for client in server.clients:
      if server.clients[client]["socket"] != self.request:
        if "player" in server.clients[client]:
          server.clients[client]["player"].notifications_buffer = bytes(message, "utf-8")

  def set_response_buffer(self, message, append = False):
    if append:
      if self.player:
        self.response_buffer += bytes(str(message), "utf-8") + self.player.notifications_buffer
      else:
        self.response_buffer += bytes(str(message), "utf-8")
    else:
      if self.player:
        self.response_buffer = bytes(str(message), "utf-8") + self.player.notifications_buffer
      else:
        self.response_buffer = bytes(str(message), "utf-8")


class ThreadedTCPServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
  pass

if __name__ == "__main__":
  global server   
  server = Server("localhost", 9999)
  server.start()