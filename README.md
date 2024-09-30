# Socket Chat Application

Welcome to the **Socket Chat Application**, a simple yet powerful tool for real-time communication over the network. This project showcases the capabilities of socket programming in C, allowing multiple clients to connect to a server, send messages, and receive broadcasts in real-time.

## 🚀 Overview

In this project, you will find a client-server architecture built using TCP sockets. The server listens for incoming client connections and broadcasts messages received from one client to all other connected clients. The client allows users to send and receive messages, creating an interactive chat environment.

## 🌟 Features

- **Real-time Messaging**: Clients can send messages that are instantly broadcasted to all other clients connected to the server.
- **Multi-client Support**: The server can handle multiple client connections concurrently using threads.
- **User-Friendly Interface**: Users can easily type their messages and see incoming messages in the terminal.

## 📦 Requirements

- C Compiler (gcc)
- POSIX threads library (pthreads)
- Standard C library

## 🛠️ Setup Instructions

1. **Clone the repository**:
   ```bash
   git clone https://github.com/yourusername/socket-chat-app.git
   cd socket-chat-app
