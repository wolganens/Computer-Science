import socket
import sys
from ScreenHelper import ScreenHelper

class Client(object):
    
    ip = "localhost"
    port = 9999
    screen_helper = ScreenHelper()    
    def __init__(self):
        super(Client, self).__init__()
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
            sock.connect((self.ip, self.port))
            self.screen_helper.start_screen()
            while True:
                self.screen_helper.clear_screen()
                self.send(sock)
                self.screen_helper.response = self.receive(sock)
                self.screen_helper.process_response()
                if self.screen_helper.arguments == "exit":
                    sock.close()
                    print("Até a próxima")
                    break

    def receive(self, sock):
        return str(sock.recv(1024), 'utf-8')

    def send(self, sock):        
        return sock.sendall(
            bytes("{} {}".format(
                    self.screen_helper.command,
                    self.screen_helper.arguments
                )
                , "utf-8")            
            )

    def close(self):
        self.socket.close()
    
if __name__ == "__main__":
    global server   
    client = Client()