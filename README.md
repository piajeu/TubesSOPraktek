# TubesSOPraktek 🎓

## Aplikasi Chat Berbasis C dan Websocket 💬

Repositori ini berisi dua program yang menunjukkan implementasi aplikasi chat secara real-time menggunakan teknologi berbeda:

1. **Aplikasi Chat Berbasis Socket (C) 🖥️**
    - Aplikasi berbasis command-line yang menggunakan socket dan `fork()` untuk menangani banyak klien.
    - Terdiri dari program server (`server.c`) dan klien (`client.c`).
2. **Aplikasi Chat Berbasis WebSocket 🌐**
    - Aplikasi chat berbasis web yang dibangun menggunakan Node.js dan WebSocket.
    - Terdiri dari server WebSocket (`server_webS.js`) dan antarmuka pengguna berbasis web (`client_webS.html`).

Kedua aplikasi ini memberikan wawasan tentang pendekatan komunikasi real-time, baik dari sisi networking level rendah (C sockets) maupun teknologi modern (WebSocket API).

---

## 1. Aplikasi Chat Berbasis Socket (C) 🖥️

### ✨ Fitur

- 🔄 Menangani banyak klien secara bersamaan menggunakan `fork()`.
- 🆔 Setiap klien memiliki username unik.
- 📢 Mendukung pesan broadcast dan perintah untuk keluar.
- 📜 Mencatat log koneksi dan pemutusan koneksi klien.

### 🔍 Cara Kerja

1. **Server**
    - 🛠️ Mendengarkan koneksi klien pada port `8080`.
    - 🔧 Membuat proses baru untuk setiap klien yang terhubung.
    - ⚙️ Menggunakan socket TCP untuk memastikan transmisi data yang andal.
2. **Klien**
    - 🌐 Menghubungkan ke server melalui socket TCP.
    - 📝 Meminta pengguna memasukkan username.
    - ✉️ Mengizinkan pengguna mengirim pesan dan menerima respon server secara real-time.
  
### Fitur Utama Code

1. **Server**
    1. **`socket()`**
    
        Membuat endpoint komunikasi untuk server.
    
    2. **`bind()`**
        
        Mengikat socket ke alamat IP dan port tertentu.
        
    3. **`listen()`**
        
        Mengatur socket dalam mode "listening", sehingga siap menerima koneksi masuk.
        
    4. **`accept()`**
        
        Menerima koneksi klien dan menghasilkan socket baru untuk komunikasi.
        
    5. **`fork()`**
        
        Membagi proses menjadi dua:
        
        - **Proses induk**: Kembali ke loop untuk menerima klien berikutnya.
        - **Proses anak**: Menangani komunikasi dengan klien spesifik.
    6. **`recv()`**
        
        Menerima data dari klien.
        
    7. **`send()`**
        
        Mengirim data ke klien.
        
    8. **`inet_ntop()`**
        
        Mengubah alamat IP dari bentuk biner ke string yang dapat dibaca manusia.
        
    9. **`close()`**
        
        Menutup socket untuk mengakhiri komunikasi.
   
2. **Klien**
    1. **`socket()`**
    
        Membuat endpoint komunikasi untuk client.
    
    2. **`connect()`**
        
        Menghubungkan client ke server pada alamat dan port tertentu.
        
    3. **`recv()`**
        
        Menerima data dari server.
        
    4. **`send()`**
        
        Mengirim data ke server.
        
    5. **`inet_pton()`**
        
        Mengonversi alamat IP dari format string ke bentuk biner.
        
    6. **`close()`**
        
        Menutup socket untuk mengakhiri koneksi.


### ▶️ Cara Penggunaan

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
    
4. Kirim dan terima pesan untuk berinteraksi. 📨

---

## 2. Aplikasi Chat Berbasis WebSocket 🌐

### ✨ Fitur

- ⚡ Pesan real-time menggunakan teknologi WebSocket.
- 💻 Antarmuka web yang mudah digunakan dengan dukungan username.
- 📢 Pesan dikirimkan ke semua klien yang terhubung.
- ✅ Menangani pemutusan koneksi klien dengan baik.

### 🔍 Cara Kerja

1. **Server**
    - 🖧 Menyediakan server WebSocket pada port `3000`.
    - 🗂️ Menyajikan file HTML untuk antarmuka pengguna.
    - 🔄 Mengelola klien yang terhubung dan menyiarkan pesan dalam format JSON.
2. **Klien**
    - 🌐 Antarmuka chat berbasis browser yang dibangun menggunakan HTML, CSS, dan JavaScript.
    - 🔌 Menghubungkan ke server WebSocket pada `ws://localhost:3000`.
    - ✏️ Memungkinkan pengguna mengatur username dan mengirim pesan.

### Fitur Utama Code

1. **Server**
    1. **`http.createServer()`**
    
        Membuat server HTTP untuk melayani permintaan klien, seperti menyajikan file HTML.
    
    2. **`fs.readFile()`**
        
        Membaca file dari sistem lokal untuk dikirimkan sebagai respons HTTP.
        
    3. **`WebSocket.Server()`**
        
        Membuat server WebSocket untuk menangani komunikasi real-time antara klien dan server.
        
    4. **`wss.on('connection')`**
        
        Mendeteksi koneksi baru dari klien WebSocket dan menambahkannya ke daftar koneksi aktif.
        
    5. **`ws.on('message')`**
        
        Mendeteksi pesan yang dikirim oleh klien dan memprosesnya, seperti mengubah username atau mendistribusikan pesan ke semua klien.
        
    6. **`clients.forEach()`**
        
        Mengiterasi semua klien aktif untuk mengirimkan pesan kepada mereka.
        
    7. **`wss.on('close')`**
        
        Mendeteksi penutupan koneksi dari klien dan menghapus klien tersebut dari daftar koneksi aktif.
        
    8. **`server.listen()`**
        
        Menjalankan server HTTP dan WebSocket pada port tertentu sehingga siap menerima permintaan dari klien.

2. **Klien**
    1. **`const ws = new WebSocket('ws://localhost:3000');`**
    
        Membuka koneksi WebSocket ke server yang berjalan di `localhost` pada port `3000`.
    
    2. **`ws.onopen`**
        
        Event yang terjadi ketika koneksi WebSocket berhasil dibuka:
        
        - Mencetak pesan log ke konsol sebagai notifikasi bahwa koneksi berhasil.
    3. **`ws.onmessage`**
        
        Event untuk menangani pesan yang diterima dari server:
        
        - Mem-parse pesan dalam format JSON menjadi objek JavaScript.
        - Membuat elemen `<p>` untuk menampilkan pesan yang sudah diformat dengan username dan teks pesan.
        - Menambahkan pesan ke elemen `#chat` dan mengatur scrollbar untuk otomatis turun ke pesan terbaru.
    4. **`sendButton.addEventListener('click')`**
        
        Event klik pada tombol "Send" memicu:
        
        - Mengambil username dari input `#username` (default: "Anonymous").
        - Memastikan bahwa pesan tidak kosong sebelum dikirim.
        - Jika username belum dikirim sebelumnya, mengirimkannya ke server sebagai objek JSON `{ username }`.
        - Mengirim teks pesan ke server sebagai objek JSON `{ message }`.
        - Membersihkan input teks setelah pesan terkirim.


### ▶️ Cara Penggunaan

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
    
4. Gunakan antarmuka chat untuk berinteraksi dengan klien lainnya. 👫

---

## 📊 Perbandingan Aplikasi

| Fitur | Chat Berbasis Socket (C) 🖥️ | Chat Berbasis WebSocket 🌐 |
| --- | --- | --- |
| **Teknologi** | Sockets, TCP, Fork | WebSocket, HTTP, Node.js |
| **Antarmuka** | Command-line | Antarmuka Web |
| **Pembaruan Real-time** | Ya | Ya |
| **Skalabilitas** | Terbatas (Fork per klien) | Lebih baik (Event-driven) |
| **Kemudahan Pengaturan** | Membutuhkan kompilasi manual | Membutuhkan runtime Node.js |

---

## 🚀 Pengembangan Masa Depan

- 🔒 Tambahkan enkripsi (contoh: TLS/SSL) untuk komunikasi yang aman.
- 👤 Implementasikan autentikasi untuk validasi pengguna.
- 🗃️ Perluas aplikasi WebSocket untuk menyimpan riwayat chat secara persisten.
- ⚡ Optimalkan server berbasis C untuk menangani lebih banyak klien secara efisien.

---

## 📚 Referensi

- [Node.js Documentation](https://nodejs.org/)
- [WebSocket API Documentation](https://developer.mozilla.org/en-US/docs/Web/API/WebSocket)
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
