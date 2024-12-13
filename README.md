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
    socket()
       Membuat endpoint komunikasi untuk server.
    bind()
       Mengikat socket ke alamat IP dan port tertentu.
    listen()
       Mengatur socket dalam mode "listening", siap menerima koneksi masuk.
    accept()
       Menerima koneksi klien dan menghasilkan socket baru untuk komunikasi.
    fork()
       Membagi proses menjadi dua:
       o Proses induk: Kembali ke loop untuk menerima klien berikutnya.
       o Proses anak: Menangani komunikasi dengan klien spesifik.
    recv()
       Menerima data dari klien.
    send()
       Mengirim data ke klien.
    inet_ntop()
       Mengubah alamat IP dari bentuk biner ke string yang bisa dibaca manusia.
    close()
       Menutup socket untuk mengakhiri komunikasi.
   
3. **Klien**
    socket()
    •	Membuat endpoint komunikasi untuk client.
    connect()
    •	Menghubungkan client ke server pada alamat dan port tertentu.
    recv()
    •	Menerima data dari server.
    send()
    •	Mengirim data ke server.
    inet_pton()
    •	Mengonversi alamat IP dari format string ke biner.
    close()
    •	Menutup socket untuk mengakhiri koneksi.


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
    http.createServer()
    •	Membuat server HTTP untuk melayani permintaan klien, seperti menyajikan file HTML.
    fs.readFile()
    •	Membaca file dari sistem lokal untuk dikirimkan sebagai respons HTTP.
    WebSocket.Server()
    •	Membuat server WebSocket untuk menangani komunikasi real-time antara klien dan server.
    wss.on('connection')
    •	Mendeteksi koneksi baru dari klien WebSocket dan menambahkannya ke daftar koneksi aktif.
    ws.on('message')
    •	Mendeteksi pesan yang dikirim oleh klien dan memprosesnya, termasuk mengubah username atau mendistribusikan pesan ke semua klien.
    clients.forEach()
    •	Mengiterasi semua klien aktif untuk mengirimkan pesan ke mereka.
    wss.on('close')
    •	Mendeteksi penutupan koneksi dari klien dan menghapus klien tersebut dari daftar koneksi aktif.
    server.listen()
    •	Menjalankan server HTTP dan WebSocket pada port tertentu sehingga siap menerima permintaan dari klien.

2. **Klien**
    const ws = new WebSocket('ws://localhost:3000');
    •	Membuka koneksi WebSocket ke server yang berjalan di localhost pada port 3000.
    ws.onopen
    •	Event yang terjadi ketika koneksi WebSocket berhasil dibuka. Hanya mencetak pesan log ke konsol sebagai notifikasi bahwa koneksi berhasil.
    ws.onmessage
    •	Event untuk menangani pesan yang diterima dari server:
        o	Pesan dalam format JSON diparse ke objek JavaScript.
        o	Elemen <p> dibuat untuk menampilkan pesan, memformatnya dengan username dan teks pesan.
        o	Pesan ditambahkan ke elemen #chat, dan scrollbar otomatis turun ke pesan terbaru.
    sendButton.addEventListener('click')
    •	Event klik pada tombol "Send" memicu:
        o	Mengambil username dari input #username (default: "Anonymous").
        o	Memastikan pesan tidak kosong sebelum dikirim.
        o	Jika username belum dikirim sebelumnya, mengirimnya ke server sebagai objek JSON { username }.
        o	Mengirim teks pesan sebagai objek JSON { message }.
        o	Membersihkan input teks setelah pesan terkirim.


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
