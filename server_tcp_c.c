//Fisiere antet necesare pentru biblioteca standard C si programare socket
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//directive de preprocesor care definesc constante
#define BUFFER_SIZE 1024 //dimensiunea buffer-ului utilizat pentru trimiterea/primirea datelor
#define SERVER_PORT 8424 //numărul portului pe care serverul va asculta conexiunile de intrare
#define FILE_PATH "./fisiere/" //calea către directorul care conține fișierele care pot fi solicitate de clienți

// Funcție de gestionare a solicitărilor clienților
void handle_client(int client_socket, pid_t client_pid) { //Ia socket-ul clientului și ID-ul procesului client ca parametri
    char buffer[BUFFER_SIZE]; //buffer-ul este folosit pentru a stoca datele primite
    ssize_t bytes_received; //reține numărul de octeți primiți

    // Se primeste numele de fisier de la client
    memset(buffer, 0, BUFFER_SIZE); //se umple buffer-ul cu 0
    bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0); //folosit pentru a primi date de la clientul socket
    if (bytes_received < 0) { //Dacă există o eroare la primirea datelor, 
        perror("Eroare la primirea numelui de fisier de la client"); //este tipărit un mesaj de eroare 
        return; //si se iese din functie
    }

    // se deschide fisierul solicitat
    char file_path[100]; 
    strcpy(file_path, FILE_PATH); //se construieste calea fisierului
    strcat(file_path, buffer); //se adauga numelui fișierului primit la directorul FILE_PATH
    FILE* file = fopen(file_path, "rb"); //se deschide fisierul in modul binar pentru citire
    if (file == NULL) { //daca fisierul nu exista
        printf("Fisier inexistent: %s (PID client: %d)\n", buffer, client_pid);
        send(client_socket, "Eroare", 6, 0); //se trimite un raspuns de eroare la client
        return; //se iese din functie
    }

    // Se trimite catre client fisierul pe bucati
    memset(buffer, 0, BUFFER_SIZE); //se goleste buffer-ul
    size_t bytes_read;
    //se citesc datele din fisier in buffer folosind fread
    while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, file)) > 0) { 
        //se citesc si se trimit date pana cand se ajunge la sfarsitul fisierului
        send(client_socket, buffer, bytes_read, 0); //se trimit datele catre client folosind send
        memset(buffer, 0, BUFFER_SIZE); //se goleste buffer-ul dupa fiecare operatie de trimitere
    }

    // Se inchide fisierul si conexiunea la client dupa ce fisierul a fost complet trimis
    fclose(file);
    close(client_socket);
}

int main() {
    int server_socket, client_socket; //se declara variabile pentru socket-urile de client si server
    struct sockaddr_in server_address, client_address; //se declara variabile pentru adresele de client si server
    socklen_t client_address_length = sizeof(client_address); //se stocheaza lungimea adresei clientului

    // Se creeaza server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // se specifica pentru socket:familia de adrese (`AF_INET` pentru IPv4), 
    // tipul de socket (`SOCK_STREAM` pentru un socket TCP) 
    // și protocolul (`0` pentru protocolul implicit al tipului de socket specificat)
    if (server_socket < 0) { //daca crearea socke-ului esueaza
        perror("Eroare la creare socket");
        exit(EXIT_FAILURE); //programul se inchide din cauza erorii
    }

    // Se leaga socketul de server la portul specificat
    // se initializeaza structura server_address cu informațiile despre adresa serverului
    server_address.sin_family = AF_INET; //se seteaza familia de adrese la AF_INET
    server_address.sin_port = htons(SERVER_PORT); 
    //se seteaza numărul portului la SERVER_PORT (convertit în ordinea octeților de rețea folosind htons) 
    server_address.sin_addr.s_addr = INADDR_ANY; 
    //se seteaza adresa IP la INADDR_ANY (permițând socketului să se lege la orice interfață de rețea disponibilă)
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) { 
        //Funcția bind leagă socket-ul serverului la adresa specificată
        perror("Eroare la obtinerea adresei"); 
        exit(EXIT_FAILURE); //Dacă legarea eșuează se închide cu o stare de eșec
    }

    // Se asculta conexiunile primite
    if (listen(server_socket, 5) < 0) { 
        //Funcția de ascultare ia socket-ul serverului și o valoare de backlog (5 în acest caz) ca parametri
        perror("Eroare la obtinerea cozii de cereri");
        exit(EXIT_FAILURE); //daca operatia de listen esueaza, programul se inchide
    }

    printf("Server deschis la portul %d\n", SERVER_PORT); 

    // Se accepta si se gestioneaza conexiunile clientilor
    while (1) { //așteaptă conexiunile primite de la clienți care utilizează funcția de acceptare
        //se acceptă cererea de conectare, creând un nou socket (client_socket) pentru comunicarea cu clientul
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Eroare la acceptarea conexiunii");
            exit(EXIT_FAILURE); //daca acceptarea esueaza, programul se inchide
        }

        // Se creeaza un proces sau fir de executie pentru a gestiona clientul
        pid_t client_pid = fork(); //Funcția fork este apelată pentru a crea un nou proces
        if (client_pid == 0) { //Dacă fork returnează 0, înseamnă că procesul curent este procesul copil
            close(server_socket); //Procesul copil închide socket-ul serverului  
            handle_client(client_socket, getpid()); // se apelează funcția handle_client pentru a procesa cererea clientului 
            exit(EXIT_SUCCESS); //se iese cu o stare de succes
        }
        else if (client_pid > 0) { //Dacă fork returnează o valoare pozitivă, înseamnă că procesul curent este procesul părinte 
            close(client_socket); //se inchide sochetul clientului
            printf("Client nou conectat: PID %d\n", client_pid);
        }
        else { //Dacă furk returnează o valoare negativă, aceasta indică o eroare
            perror("Eroare la bifurcare");
            exit(EXIT_FAILURE);
        }

    }

    // Se inchide socketul
    close(server_socket);

    return 0;
}
