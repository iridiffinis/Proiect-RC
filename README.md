# Proiect - Rețele de calculatoare
## Programe TCP client-server in C și Python
### 1.	Program TCP client-server în C
Acest program permite transferul de fișiere de la server la client prin intermediul protocolului TCP. Serverul gestionează cererile primite de la clienți și trimite fișierele solicitate, în timp ce clientul se conectează la server, solicită fișiere și le primește.
Funcționalitatea serverului constă în ascultarea conexiunilor de intrare pe un port specificat. Când un client se conectează la server, acesta creează un proces sau fir de execuție separat pentru a gestiona cererea clientului. Serverul primește de la client un nume de fișier și verifică existența acestuia în directorul specificat. Dacă fișierul există, acesta este trimis către client în bucăți, iar conexiunea se închide după ce fișierul a fost complet trimis.
Funcționalitatea clientului constă în conectarea la server folosind adresa IP și portul specificate. Clientul solicită un fișier de la server prin introducerea numelui de fișier. Apoi, clientul trimite numele fișierului către server, iar serverul verifică existența fișierului. Dacă fișierul există, acesta este primit de către client și salvat local.

![image](https://github.com/iridiffinis/Proiect-RC/assets/102820231/7fc142ed-c90d-4c60-8b13-c472cef8d087)


### 2.	Program TCP client-server în Python
Acest program implementează un server și un client TCP care comunică prin intermediul socket-urilor. Serverul primește mesaje de la client, le criptează folosind un cifru Caesar cu o schimbare de 3 și le trimite înapoi către client, împreună cu timpul de criptare.
Serverul așteaptă conexiuni de la clienți pe o anumită adresă IP și port specificat. După ce primește o conexiune, serverul primește mesajul de la client, îl criptează, măsoară timpul de criptare și trimite mesajul criptat și timpul de criptare înapoi la client. Acest lucru se întâmplă într-un fir de execuție separat pentru fiecare client.
Clientul se conectează la serverul specificat prin adresa IP și portul corespunzător. Apoi, clientul trimite un mesaj către server. După ce primește răspunsul de la server, clientul decodifică răspunsul și afișează mesajul criptat și timpul de criptare.

![image](https://github.com/iridiffinis/Proiect-RC/assets/102820231/20f522e4-4a93-4366-9382-5300a3e06aa5)
