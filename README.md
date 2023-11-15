# Project - Computer Networks
## TCP client-server programs in C and Python
### 1.	TCP client-server program in C
This program allows the transfer of files from the server to the client via the TCP protocol. The server handles requests received from clients and sends the requested files, while the client connects to the server, requests files, and receives them.
The functionality of the server is to listen for incoming connections on a specified port. When a client connects to the server, it creates a separate process or thread to handle the client's request. The server receives a file name from the client and checks for its existence in the specified directory. If the file exists, it is sent to the client in chunks, and the connection closes after the file has been completely sent.
The functionality of the client is to connect to the server using the specified IP address and port. The client requests a file from the server by entering the file name. The client then sends the file name to the server, and the server verifies that the file exists. If the file exists, it is received by the client and saved locally.

![image](https://github.com/iridiffinis/Proiect-RC/assets/102820231/7fc142ed-c90d-4c60-8b13-c472cef8d087)


### 2.	TCP client-server program in Python
This program implements a TCP server and client that communicate via sockets. The server receives messages from the client, encrypts them using a Caesar cipher with a shift of 3, and sends them back to the client, along with the encryption time.
The server waits for connections from clients on a specific IP address and specified port. After receiving a connection, the server receives the message from the client, encrypts it, measures the encryption time, and sends the encrypted message and encryption time back to the client. This happens in a separate thread for each client.
The client connects to the specified server via the corresponding IP address and port. The client then sends a message to the server. After receiving the response from the server, the client decodes the response and displays the encrypted message and encryption time.

![image](https://github.com/iridiffinis/Proiect-RC/assets/102820231/20f522e4-4a93-4366-9382-5300a3e06aa5)
