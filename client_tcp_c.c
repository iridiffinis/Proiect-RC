//Fisiere antet necesare pentru biblioteca standard C si programare socket
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

//se definesc constante folosind directive de preprocesare
#define BUFFER_SIZE 1024 //dimensiunea buffer - ului utilizat pentru trimiterea / primirea datelor
#define SERVER_IP "37.120.249.45" //adresa IP a serverului
#define SERVER_PORT 8424 //numărul portului pe care ascultă serverul

// Functie pentru a primi un fisier de la server
void receive_file(int client_socket, const char* file_name) { 
    //se iau socket-ul clientului si numele fisierului ca paramnetru
    FILE* file = fopen(file_name, "wb"); //se deschide un nou fisier in modul de scriere binar ("wb")
    if (file == NULL) { //daca fisierul nu poate fi creat
        perror("Eroare la crearea fisierului");
        return; //se iese din functie
    }

    char buffer[BUFFER_SIZE]; //se declara buffer pentru a stoca datele primite
    ssize_t bytes_received; //variabila pentru numarul de octeti primiti la fiecare operatie de citire
    size_t total_bytes_received = 0; //numarul total de octeti primiti

    // Se primesc datele fisierului pe bucati si se scrie in fisier
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0)) > 0) {
        //numărul de octeți primiți în fiecare iterație este stocat în bytes_received
        fwrite(buffer, sizeof(char), bytes_received, file); //Datele primite sunt scrise în fișier
        total_bytes_received += bytes_received; //se actualizeaza numarul total de octeti primiti
    } //bucla continua pana cand nu mai sunt date de primit

    fclose(file); //se inchide fisierul dupa ce s-au primit toate datele

    if (bytes_received < 0) { //daca exita erori la primirea datelor
        perror("Eroare la primirea datelor fisierului de la server");
        return;
    }

    printf("Fisier primit: %s (%zu bytes)\n", file_name, total_bytes_received);
}

int main() {
    int client_socket; //variabila petnru socket-ul client
    struct sockaddr_in server_address; //variabila pentru adresa serverului

    // Creare client socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    //se specifica familia de adrese (AF_INET pentru IPv4)
    // tipul de socket (`SOCK_STREAM` pentru un socket TCP)
    //și protocolul(`0` pentru protocolul implicit al tipului de socket specificat)
    if (client_socket < 0) { //daca crearea socke-ului esueaza
        perror("Eroare la creare socket");
        exit(EXIT_FAILURE);
    }

    // Se seteaza adresa serverului
    server_address.sin_family = AF_INET; //se seteaza familia de adrese la AF_INET
    server_address.sin_port = htons(SERVER_PORT); 
    //se seteaza numărul portului la SERVER_PORT (convertit în ordinea octeților de rețea folosind htons)
    if (inet_pton(AF_INET, SERVER_IP, &(server_address.sin_addr)) <= 0) { 
        //convertește adresa IP a serverului din formatul de prezentare în formatul de rețea folosind inet_pton
        perror("Eroare in convertirea adresei IP a serverului");
        exit(EXIT_FAILURE);
    }

    // Conectarea la server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Eroare la obtinerea conexiunii");
        exit(EXIT_FAILURE);
    }

    // Solicitare fisier de la server
    char file_name[100];
    printf("Introduceti numele fisierului solicitat de la server: ");
    scanf("%s", file_name); //stocheaza numele fisierului in vector

    send(client_socket, file_name, strlen(file_name), 0); //trimite numele fisierului catre server, prin functia send

    // Primire fisier de la server
    receive_file(client_socket, file_name); //fisierul se salveaza local

    // Inchidere client socket
    close(client_socket);

    return 0;
}

