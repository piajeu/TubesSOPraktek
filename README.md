# TubesSOPraktek
# Aplikasi Chat Berbasis WebSocket

## Deskripsi

Repositori ini berisi dua program yang menunjukkan implementasi aplikasi chat secara real-time menggunakan teknologi berbeda:

1. **Aplikasi Chat Berbasis Socket (C)**
    - Aplikasi berbasis command-line yang menggunakan socket dan `fork()` untuk menangani banyak klien.
    - Terdiri dari program server (`server.c`) dan klien (`client.c`).
2. **Aplikasi Chat Berbasis WebSocket**
    - Aplikasi chat berbasis web yang dibangun menggunakan Node.js dan WebSocket.
    - Terdiri dari server WebSocket (`server_webS.js`) dan antarmuka pengguna berbasis web (`client_webS.html`).

Kedua aplikasi ini memberikan wawasan tentang pendekatan komunikasi real-time, baik dari sisi networking level rendah (C sockets) maupun teknologi modern (WebSocket API).

---

## 1. Aplikasi Chat Berbasis Socket (C)

### Fitur

- Menangani banyak klien secara bersamaan menggunakan `fork()`.
- Setiap klien memiliki username unik.
- Mendukung pesan broadcast dan perintah untuk keluar.
- Mencatat log koneksi dan pemutusan koneksi klien.

### Cara Kerja

1. **Server**
    - Mendengarkan koneksi klien pada port `8080`.
    - Membuat proses baru untuk setiap klien yang terhubung.
    - Menggunakan socket TCP untuk memastikan transmisi data yang andal.
2. **Klien**
    - Menghubungkan ke server melalui socket TCP.
    - Meminta pengguna memasukkan username.
    - Mengizinkan pengguna mengirim pesan dan menerima respon server secara real-time.

### Cara Penggunaan

1. Kompilasi program server dan klien:
    
    ```bash
    
    gcc -o server server.c
    gcc -o client client.c
    
    ```
    
2. Jalankan server:
    
    ```bash
    
    ./server
    
    ```
    
3. Jalankan beberapa klien:
    
    ```bash
    
    ./client
    
    ```
    
4. Kirim dan terima pesan untuk berinteraksi.

---

## 2. Aplikasi Chat Berbasis WebSocket

### Fitur

- Pesan real-time menggunakan teknologi WebSocket.
- Antarmuka web yang mudah digunakan dengan dukungan username.
- Pesan dikirimkan ke semua klien yang terhubung.
- Menangani pemutusan koneksi klien dengan baik.

### Cara Kerja

1. **Server**
    - Menyediakan server WebSocket pada port `3000`.
    - Menyajikan file HTML untuk antarmuka pengguna.
    - Mengelola klien yang terhubung dan menyiarkan pesan dalam format JSON.
2. **Klien**
    - Antarmuka chat berbasis browser yang dibangun menggunakan HTML, CSS, dan JavaScript.
    - Menghubungkan ke server WebSocket pada `ws://localhost:3000`.
    - Memungkinkan pengguna mengatur username dan mengirim pesan.

### Cara Penggunaan

1. Instal dependensi:
    
    ```bash
    
    npm install ws
    
    ```
    
2. Jalankan server:
    
    ```bash
    
    node server.js
    
    ```
    
3. Buka klien chat di browser:
    
    ```bash
    
    http://localhost:3000/
    
    ```
    
4. Gunakan antarmuka chat untuk berinteraksi dengan klien lainnya.

---

## Perbandingan Aplikasi

| Fitur | Chat Berbasis Socket (C) | Chat Berbasis WebSocket |
| --- | --- | --- |
| Teknologi | Sockets, TCP, Fork | WebSocket, HTTP, Node.js |
| Antarmuka | Command-line | Antarmuka Web |
| Pembaruan Real-time | Ya | Ya |
| Skalabilitas | Terbatas (Fork per klien) | Lebih baik (Event-driven) |
| Kemudahan Pengaturan | Membutuhkan kompilasi manual | Membutuhkan runtime Node.js |

---

## Pengembangan Masa Depan

- Tambahkan enkripsi (contoh: TLS/SSL) untuk komunikasi yang aman.
- Implementasikan autentikasi untuk validasi pengguna.
- Perluas aplikasi WebSocket untuk menyimpan riwayat chat secara persisten.
- Optimalkan server berbasis C untuk menangani lebih banyak klien secara efisien.

---

## Referensi

- [Node.js Documentation](https://nodejs.org/)
- [WebSocket API Documentation](https://developer.mozilla.org/en-US/docs/Web/API/WebSocket)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)