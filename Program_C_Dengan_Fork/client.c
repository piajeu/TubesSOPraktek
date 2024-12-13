#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // Menampilkan PID dari proses client
    printf("Client berjalan (PID: %d)...\n", getpid());

    // Membuat socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Gagal membuat socket");
        exit(EXIT_FAILURE);
    }

    // Mengatur alamat server
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Alamat tidak valid");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    // Terhubung ke server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Gagal terhubung ke server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    printf("Terhubung ke server. Ketik 'exit' untuk keluar.\n");

    // Terima pesan awal dari server
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    // Kirim username
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Hapus karakter newline
    send(client_socket, buffer, strlen(buffer), 0);

    // Interaksi dengan server
    while (1) {
        printf("> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0; // Hapus karakter newline

        // Kirim pesan ke server
        send(client_socket, buffer, strlen(buffer), 0);

        // Periksa jika klien ingin keluar
        if (strcmp(buffer, "exit") == 0) {
            printf("Keluar dari server.\n");
            break;
        }

        // Terima balasan dari server
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            printf("Server: %s\n", buffer);
        } else {
            printf("Koneksi dengan server terputus.\n");
            break;
        }
    }

    close(client_socket);
    return 0;
}
