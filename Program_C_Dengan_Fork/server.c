#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Fungsi untuk menangani setiap klien
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    char username[50];
    int bytes_read;

    // Minta username dari klien
    send(client_socket, "Masukkan username Anda: ", 25, 0);
    bytes_read = recv(client_socket, username, sizeof(username) - 1, 0);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    username[bytes_read] = '\0'; // Null-terminate username
    printf("Klien '%s' terhubung (PID: %d).\n", username, getpid());

    // Loop untuk menerima pesan dari klien
    while ((bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate pesan
        printf("[%s]: %s\n", username, buffer);

        // Periksa jika klien ingin keluar
        if (strcmp(buffer, "exit") == 0) {
            printf("Klien '%s' keluar.\n", username);
            break;
        }

        // Kirim kembali pesan ke klien (echo)
        send(client_socket, buffer, bytes_read, 0);
    }

    close(client_socket);
    printf("Koneksi dengan klien '%s' ditutup (PID: %d).\n", username, getpid());
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Membuat socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Gagal membuat socket");
        exit(EXIT_FAILURE);
    }

    // Mengatur alamat server
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket ke alamat
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind gagal");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Dengarkan koneksi masuk
    if (listen(server_socket, 5) < 0) {
        perror("Listen gagal");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server berjalan di port %d (PID: %d)...\n", PORT, getpid());

    // Menangani klien dengan fork
    while ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) >= 0) {
        // Log alamat IP dan port klien
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        int client_port = ntohs(client_addr.sin_port);
        printf("Connection accepted from %s:%d\n", client_ip, client_port);

        pid_t child_pid = fork();
        if (child_pid == 0) {
            // Proses anak
            close(server_socket); // Tutup socket server di proses anak
            handle_client(client_socket);
            exit(0);
        } else if (child_pid > 0) {
            // Proses induk
            printf("Proses anak dengan PID %d dibuat oleh PID %d.\n", child_pid, getpid());
            close(client_socket); // Tutup socket klien di proses induk
        } else {
            perror("Fork gagal");
        }
    }

    close(server_socket);
    return 0;
}
