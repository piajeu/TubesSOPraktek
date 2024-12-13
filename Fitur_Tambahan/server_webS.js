const http = require('http');
const WebSocket = require('ws');
const fs = require('fs');
const path = require('path');

// Menampilkan informasi PID dan PPID
console.log("Server Process Information:");
console.log("PID (Process ID):", process.pid);
console.log("PPID (Parent Process ID):", process.ppid);

// Membuat server HTTP untuk mengirimkan file HTML
const server = http.createServer((req, res) => {
    const filePath = path.join(__dirname, 'client_webS.html');
    fs.readFile(filePath, (err, content) => {
        if (err) {
            console.error('Error reading HTML file:', err);
            res.writeHead(500);
            res.end('Server Error: Unable to load HTML file');
            return;
        }
        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(content);
    });
});

// Membuat WebSocket server
const wss = new WebSocket.Server({ server });

// Menyimpan koneksi WebSocket klien beserta username
let clients = [];

wss.on('connection', (ws) => {
    console.log('A client connected');
    
    // Menambahkan klien baru ke array clients dengan username default
    ws.username = 'Anonymous';
    clients.push(ws);
    
    // Menangani pesan yang diterima dari klien
    ws.on('message', (message) => {
        try {
            const data = JSON.parse(message); // Parsing pesan dalam format JSON
            
            // Jika pesan mengandung username, perbarui username klien
            if (data.username) {
                ws.username = data.username;
                console.log(`Client set username to: ${ws.username}`);
                return;
            }
            
            // Jika pesan adalah teks, log pesan di server dan kirimkan ke semua klien
            if (data.message) {
                const formattedMessage = JSON.stringify({
                    username: ws.username,
                    message: data.message
                });

                // Tampilkan pesan di server
                console.log(`[${ws.username}]: ${data.message}`);
                
                // Kirimkan pesan ke semua klien
                clients.forEach((client) => {
                    if (client.readyState === WebSocket.OPEN) {
                        client.send(formattedMessage);
                    }
                });
            }
        } catch (err) {
            console.error('Error processing message:', err);
        }
    });

    // Menangani penutupan koneksi
    ws.on('close', () => {
        clients = clients.filter(client => client !== ws);
        console.log(`${ws.username} disconnected`);
    });
});

// Menjalankan server di port 3000
server.listen(3000, () => {
    console.log('Server running at http://localhost:3000/');
});
