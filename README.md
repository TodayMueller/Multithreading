# Multithreading

The project consists of two programs: a client and a server, which facilitate interaction between the user and the server over the network. The client program allows data input, while the server processes it and returns the results to the client.

The project is implemented in C++ and incorporates the following technical aspects:

- Multithreading: The project employs multithreading for parallel data processing and client interaction.
- Network Communication: Network sockets and protocols are used for data exchange between the client and server.
- Client-Server Architecture: The project is structured with a client-server architecture where clients send requests to the server, and the server processes them and sends back responses.

To run the project, follow these steps:

1. Compile the client program using CMake.
2. Compile the server program, also using CMake.
3. Start the server program, which will begin listening for incoming connections on port 8080.
4. Launch the client program and start inputting data. It will be sent to the server for processing.
5. To exit the program, input "exit" in the client program.
