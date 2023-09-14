import socket #oferă funcțiile și clasele necesare pentru programarea socket-ului

#functia de trimitere a mesajului
def send_message(server_host, server_port, message):
    #primeste ca parametrii hostul serverului, portul serverului si mesajul
    #creare socket client specificând familia de adrese (socket.AF_INET pentru IPv4)
    # și tipul de socket (socket.SOCK_STREAM pentru TCP)
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((server_host, server_port)) #socketul client este conectat la portul serverului
    
    client_socket.send(message.encode('utf-8')) #trimite mesajul către server prin codificarea lui ca UTF-8
    response = client_socket.recv(1024).decode('utf-8') #așteaptă să primească răspunsul de la server
    #Răspunsul primit este în octeți, deci este decodat într-un șir

    encrypted_msg, encryption_time = response.split(',')
    #imparte șirul de răspuns în două părți pe baza separatorului virgulă
    
    print(f"Mesaj criptat: {encrypted_msg}")
    print(f"Timp de criptare: {encryption_time} secunde")
    
    client_socket.close() #inchide socketul client

if __name__ == '__main__': #dacă scriptul este executat ca program principal
    #se atribuie valori petntru hostul si portul serverului
    server_host = '37.120.249.45'
    server_port = 8424
    
    message = input("Introduceți mesajul: ")
    send_message(server_host, server_port, message)
    #inițiază procesul de trimitere a mesajului către server pe partea clientului
    # și de primire a mesajului criptat și a timpului de criptare ca răspuns
