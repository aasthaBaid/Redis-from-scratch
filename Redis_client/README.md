# Welcome to My Cpp Redis Client
***

## Task
This project is a simple **Redis Command Line Interface (CLI)** written in **C++**.  
It allows users to **connect to a Redis server** via **TCP sockets**, send **Redis commands**,  
and **receive and parse responses** using the **RESP protocol**.  

### **Challenges**
- Implementing **low-level socket programming** to communicate with Redis.
- Parsing **Redis protocol responses (RESP)** efficiently.
- Supporting both **interactive (REPL)** and **one-shot command execution**.
- Ensuring **cross-platform compatibility** (Linux & macOS).

***

## Description
This Redis CLI was implemented using **C++** with a focus on:
1. **Networking** – Using **Berkeley sockets** to establish a TCP connection.
2. **Command Parsing** – Converting user input into Redis’ **RESP format**.
3. **Response Handling** – Processing Redis responses such as:
   - **Simple strings** (`+OK`)
   - **Errors** (`-ERROR`)
   - **Integers** (`:100`)
   - **Bulk strings** (`$5\r\nhello`)
   - **Arrays** (`*2\r\n$3\r\nfoo\r\n$3\r\nbar`)
4. **Modes of Operation**:
   - **REPL Mode** → Interactive shell (`./my_redis_cli`)
   - **One-shot Mode** → Execute a single command (`./my_redis_cli set mykey myvalue`)

***

## Installation
### **🔧 Requirements**
- **Linux/macOS**
- **G++ (C++ Compiler)**
- **Make**

### **💻 Build Instructions**
```sh
git clone https://git.us.qwasar.io/my_cpp_redis_client_178902_esxpnw/my_cpp_redis_client.git
cd my_redis_cli
make
```
This will generate the executable **`my_redis_cli`**.

***

## Usage

### **🔹 Start Interactive Mode (REPL)**
```sh
./my_redis_cli
```
Example:
```
127.0.0.1:6379> set mykey hello
OK
127.0.0.1:6379> get mykey
"hello"
127.0.0.1:6379> quit
Goodbye.
```

### **🔹 Execute a Single Command**
```sh
./my_redis_cli set mykey "hello"
OK
```

### **🔹 Connect to a Custom Redis Server**
```sh
./my_redis_cli -h 192.168.1.10 -p 6380
```

### **🔹 Show Help**
```sh
./my_redis_cli help
```

***

## Features
- ✅ **Low-level TCP connection to Redis**
- ✅ **Supports all basic Redis commands**
- ✅ **Interactive REPL shell**
- ✅ **Command-line execution**
- ✅ **RESP protocol parsing**

***

### The Core Team
Selcuk Aksoy

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px' /></span>
