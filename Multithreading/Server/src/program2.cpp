#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

class ClientHandler {
public:
    void handleClient(int client_socket) {
        char buffer[256];
        while (true) {
            std::memset(buffer, 0, sizeof(buffer));
            int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received <= 0) {
                std::cerr << "Client disconnected\n";
                break;
            }
            std::string sum = buffer;
            processSum(sum);
        }
        close(client_socket);
    }

private:
    void processSum(std::string sum) {
        if (sum.size() > 2 && std::stoi(sum) % 32 == 0) {
            std::cout << "Received sum: " << sum << std::endl;
        } else {
            std::cout << "Error. The sum is too small or not a multiple of 32" << std::endl;
        }
    }
};

class Server {
public:
    Server() {
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1) {
            std::cerr << "Error: Failed to create socket\n";
            return;
        }

        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(8080); // Используем порт 8080 для примера
        server_address.sin_addr.s_addr = INADDR_ANY;

        if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
            std::cerr << "Error: Failed to bind\n";
            close(server_socket);
            return;
        }

        if (listen(server_socket, 5) == -1) {
            std::cerr << "Error: Failed to listen\n";
            close(server_socket);
            return;
        }

        std::cout << "Server is listening on port 8080...\n";
    }

    ~Server() {
        close(server_socket);
    }

    void startListening() {
        while (true) {
            int client_socket = accept(server_socket, NULL, NULL);
            if (client_socket == -1) {
                std::cerr << "Error: Failed to accept connection\n";
                close(server_socket);
                return;
            }

            std::thread(&ClientHandler::handleClient, &clientHandler, client_socket).detach();
        }
    }

private:
    int server_socket;
    ClientHandler clientHandler;
};

int main() {
    Server server;
    server.startListening();

    return 0;
}

