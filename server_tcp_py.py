# importuri de module necesare
import socket  # oferă funcțiile și clasele necesare pentru programarea socket-ului
import threading  # folosit pentru a crea și gestiona fire
import time  # utilizat pentru măsurarea timpului de criptare

# functie pentru gestionarea fiecărei conexiuni client
def handle_client(conn, addr):  # primeste conexiunea clientului si adresa ca parametri
    while True:  # bucla infinita pentru a primi continuu date de la client
        data = conn.recv(1024).decode('utf-8')
        if not data:  # daca nu sunt primite date, bucla se intrerupe
            break

        encrypted_msg = caesar_encrypt(data, 3)
        # Criptarea mesajului prin apelarea functiei pentru a cripta datele primite folosind un cifru Caesar cu o schimbare de 3

        # Calcularea timpului de criptare
        start_time = time.time()  # capturarea orei de începere  folosind time.time()
        time.sleep(1)  # Simularea unui timp de criptare mai mare, introducandu-se o întârziere artificială de 1 secundă
        end_time = time.time()  # se capteaza ora de sfarsit
        encryption_time = end_time - start_time  # Timpul de criptare se calculează scăzând ora de începere din timpul de sfârșit

        response = encrypted_msg + ',' + str(
            encryption_time)  # pregătește mesajul de răspuns prin concatenarea mesajului criptat și a timpului de criptare
        conn.send(response.encode(
            'utf-8'))  # rapuns trimis inapoi catre client prin codificarea lui ca UTF-8 și folosind conn.send()

    conn.close()  # se inchide conexiunea cu clientul


# Functia de criptare a mesajului
def caesar_encrypt(msg, shift):  # parametri sunt mesajul si valoarea de schimb intre litere
    encrypted_msg = ""
    for char in msg:  # Iterează peste fiecare caracter din mesaj
        if char.isalpha():  # verifică dacă este un caracter alfabetic
            encrypted_char = chr((ord(char) - ord('a') + shift) % 26 + ord('a'))
            # se face criptarea Caesar prin deplasarea valorii Unicode a caracterului cu valoarea de schimbare și împachetarea alfabetelor
            encrypted_msg += encrypted_char
        else:
            encrypted_msg += char
    return encrypted_msg  # Mesajul criptat este construit caracter cu caracter și returnat


# Functia de pornire a serverului
def start_server():
    host = '37.120.249.45'  # initializarea variabilei host cu adresa IP
    port = 8424  # numarul portului pe care asculta serverul

    # creare socket de server specificand familia de adrese (socket.AF_INET pentru IPv4) și tipul de socket (socket.SOCK_STREAM pentru TCP)
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))  # socketul server este legat la host
    server_socket.listen(5)  # seteaza socketul in starea de ascultare, permițând până la 5 conexiuni în coadă

    print(f"Serverul rulează pe adresa {host}:{port}")

    while True:  # buclă infinită pentru a accepta continuu conexiuni client
        conn, addr = server_socket.accept()
        # Când o nouă conexiune este acceptată, returnează un nou obiect socket conn reprezentând conexiunea și adresa clientului
        print(f"Conexiune nouă de la {addr[0]}:{addr[1]}")

        client_thread = threading.Thread(target=handle_client,
                                         args=(conn, addr))  # este creat un nou thred pentru a gestiona clientul
        client_thread.start()  # se porneste thred-ul client


if __name__ == '__main__':  # dacă scriptul este executat ca program principal
    start_server()  # se apleleaza functia pentru a porni serverul
