
# 🔐 Lamport Authentication Demo (Qt + Crypto++)

This project demonstrates **Lamport’s One-Way Hash Chain Authentication Protocol** using a **desktop application** built in **C++17**, **Qt6 (Widgets + Networking)**, and **Crypto++**.

Two instances of the app run as **Alice** and **Bob**, communicating over **TCP/IP** via a secure **challenge–response mechanism**.
The GUI includes **Connect**, **Start**, **Stop**, and **Disconnect** buttons, and a real-time **log window** showing protocol messages.

---

## 🧠 Theory

For a complete understanding of the protocol and its implementation, see:

* **Theoretical Working** — detailed explanation of Lamport’s one-way hash chain authentication, step-by-step message flow, verification logic, and security rationale.
* **System Design** — architecture overview, module breakdown (Crypto, Config, Network, Controller, GUI), and message formats used for communication.

---

## ⚙️ Prerequisites

### 🖥️ macOS

1. Ensure [Homebrew](https://brew.sh/) is installed.
2. Install dependencies:

   ```bash
   brew install cmake qt cryptopp
   ```

### 🐧 Linux (Debian/Ubuntu-based)

1. Update and install required packages:

   ```bash
   sudo apt update
   sudo apt install clang cmake qtbase5-dev libcrypto++-dev libqt6core6 libqt6gui6 libqt6widgets6 qt6-base-dev build-essential
   ```

---

## 🧩 Gen Chain Tool

A utility tool that generates an **initial hash chain** using Crypto++, given a random seed and desired chain length.

### 📦 Requirements

* C++17 compatible compiler (`clang++` or `g++`)
* Crypto++ library installed

---

### 🖥️ macOS

Install Crypto++ (if not already):

```bash
brew install cryptopp
```

Navigate to the tool directory:

```bash
cd tools/gen_chain
```

Compile:

```bash
PREFIX=$(brew --prefix)
clang++ -std=c++17 gen_chain.cpp -I${PREFIX}/include -L${PREFIX}/lib -lcryptopp -o gen_chain \
  -Wl,-search_paths_first -Wl,-headerpad_max_install_names
```

Run:

```bash
./gen_chain "random_seed_123" 100
```

---

### 🐧 Linux (Ubuntu/Debian/Fedora etc.)

Install Crypto++:

```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

# Fedora/RHEL
sudo dnf install cryptopp cryptopp-devel
```

Navigate and compile:

```bash
cd tools/gen_chain
g++ -std=c++17 gen_chain.cpp -lcryptopp -o gen_chain
```

Run:

```bash
./gen_chain "random_seed_123" 100
```

**Usage:**

```bash
./gen_chain <seed_string> <chain_length>
```

**Example:**

```bash
./gen_chain "my_secret_seed" 100
```

👉 Outputs the generated hash chain based on the given seed.

---

## 🔨 Build Instructions

### macOS

```bash
rm -rf build
mkdir build && cd build
cmake -DCMAKE_CXX_COMPILER=clang++ -DQt6_DIR=$(brew --prefix)/opt/qt/lib/cmake/Qt6 ..
cmake --build . -- -j$(sysctl -n hw.ncpu)
```

### Linux

```bash
rm -rf build
mkdir build && cd build
cmake -DCMAKE_CXX_COMPILER=clang++ -DQt6_DIR=/usr/lib/x86_64-linux-gnu/cmake/Qt6 ..
cmake --build . -- -j$(nproc)
```

Output executable:

```
build/lamport_app
```

---

## ▶️ Running the Demo (Same Machine)

Run **two instances** of the app — one as **Alice**, one as **Bob**.

### 1. Start Bob

```bash
cd lamport-auth
./build/lamport_app
```

In GUI:

* Click **Connect**
* Choose `config_bob.json`
* Bob starts server → `127.0.0.1:5001`

### 2. Start Alice

```bash
cd lamport-auth
./build/lamport_app
```
```
LamportAuth/
│
├── build/                     # CMake build output (generated binaries)
│
├── src/                       # Application source code
│   ├── app/                   # Application entry logic
│   ├── controller/            # Main protocol controller (state handling)
│   ├── crypto/                # Hashing, chain generation (Crypto++)
│   ├── file/lamportchain/     # Hash chain implementation
│   ├── gui/                   # Qt GUI components
│   ├── mainwindow/            # Main window (buttons, signals, logs)
│   ├── network/               # Networking layer
│   │   ├── networkmanager.cpp/h
│   ├── util/                  # Utility classes (helpers)
│   ├── configmanager.cpp/h    # Config reader (JSON/TXT)
│   ├── logger.cpp/h           # Logging utility
│   └── main.cpp               # Application entry point
│
├── test/                      # Test scripts / unit test files
│
├── tools/                     # Utility tools (e.g., hash chain generator)
│   └── gen_chain.cpp
│
├── alice_hn/                  # Alice's last known hash (hn)
├── non_h0/                    # Bob's original seed (h0)
│
├── CMakeLists.txt             # Main CMake configuration
├── cmake/                     # CMake module directory
│
├── config_alice.json          # Alice configuration (IP/Port)
├── config_bob.json            # Bob configuration (IP/Port)
│
├── README.md                  # Project documentation

```
In GUI:

* Click **Connect**
* Choose `config_alice.json`
* Alice connects to `127.0.0.1:5001`

### 3. Start Authentication

* In **Alice’s** window, click **Start**
* Authentication begins automatically with periodic (1-second) challenge–response rounds.

---

## 🌐 Running Across Two Machines

Edit configurations:

**config_alice.json**

```json
{
  "local_ip": "192.168.1.5",
  "local_port": 5000,
  "peer_ip": "192.168.1.6",
  "peer_port": 5001
}
```

**config_bob.json**

```json
{
  "local_ip": "192.168.1.6",
  "local_port": 5001,
  "peer_ip": "192.168.1.5",
  "peer_port": 5000
}
```

* Start **Bob** first (server)
* Then start **Alice** (client)

---

## 🧾 Example Logs

### Alice (Client)

```
[2025-09-07T12:45:12] Loaded Alice hn: dc35aadb...
[2025-09-07T12:45:12] Attempting to connect as client...
[2025-09-07T12:45:12] Network connected
[2025-09-07T12:45:13] Sent CHALLENGE: 1
[2025-09-07T12:45:13] Received RESPONSE: dc35aadb...
[2025-09-07T12:45:13] Verify OK for challenge 1; updated storedHash
```

### Bob (Server)

```
[2025-09-07T12:45:10] Loaded Bob h0: random_seed_123...
[2025-09-07T12:45:10] Server started and listening (role=Bob)
[2025-09-07T12:45:12] Network connected
[2025-09-07T12:45:13] Received CHALLENGE: 1
[2025-09-07T12:45:13] Sent RESPONSE for challenge 1
```

---

## 📸 Documentation

Full documentation includes:
* Source file breakdown (`main.cpp`, `network.cpp`, `crypto_utils.cpp`, etc.)
* Future enhancements (HMAC-based chain, password integration, persistent session logging)

---

## 👥 Team C21 — Cybersecurity Project (IIIT Allahabad)

| Member                       | Role                          |
| ---------------------------- | ----------------------------- |
| 👨‍💻 **Bikram Barman**      | Lead Developer                |
| 👨‍💻 **Uday Ranjan**        | Network & Config Integration  |
| 👨‍💻 **Arvind Kumar Munda** | Crypto & Chain Logic          |
| 👨‍💻 **Nikhil Chauhan**     | GUI Design & Testing          |
| 👨‍💻 **Manoj Chauhan**      | Documentation & Build Scripts |

---

## 📚 References

* Lamport, L. (1981). *Password Authentication with Insecure Communication.*
* [Crypto++ Library](https://www.cryptopp.com/)
* [Qt Framework](https://www.qt.io/)

---
