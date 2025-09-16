
# Redis-Scratch (Custom Redis Implementation in C++)

This project is a simplified **Redis-like database** built from scratch in C++.  
It consists of two main components:

1. **Redis Server (`Redis_server/`)** – Handles connections, parses commands, and manages an in-memory database.
2. **Redis Client (`Redis_client/`)** – A command-line interface (CLI) to interact with the server.

The project demonstrates core database concepts such as **command handling, in-memory storage, RDB-like persistence, and client-server communication**.

---

## 📂 Project Structure

```

REDIS\_SCRATCH/
│── Redis\_client/              # Client implementation
│   ├── Client/
│   │   ├── main.cpp           # Entry point for client
│   │   ├── my\_redis\_cli.cpp   # Client CLI implementation
│   │   ├── my\_redis\_cli.h     # Client header file
│   │   └── utils.cpp          # Utility functions
│   ├── my\_redis\_cli.dSYM/
│   └── Makefile               # Client build file
│
│── Redis\_server/              # Server implementation
│   ├── include/
│   │   ├── RedisCommandHandler.h  # Command handling interface
│   │   ├── RedisDatabase.h        # Database interface
│   │   └── RedisServer.h          # Server interface
│   ├── src/
│   │   ├── main.cpp               # Entry point for server
│   │   ├── RedisCommandHandler.cpp
│   │   ├── RedisDatabase.cpp
│   │   └── RedisServer.cpp
│   ├── dump.my\_rdb             # Example database dump file
│   ├── Makefile                # Server build file
│   └── UseCases.md             # Example use cases
│
│── README.md                   # Project documentation

````

## Build Instructions

### Build Server
```bash
cd Redis_server
make
./my_redis_server
````

### Build Client

```bash
cd Redis_client
make
./my_redis_cli
```

---

## Usage

1. Start the server:

   ```bash
   ./my_redis_server
   ```

2. In another terminal, run the client:

   ```bash
   ./my_redis_cli
   ```

3. Use Redis-like commands:

### 1. Key/Value Operations

| Command              | Example                                        | Expected Reply      |
| -------------------- | ---------------------------------------------- | ------------------- |
| **SET** / **GET**    | `SET mykey "myvalue"`<br>`GET mykey`           | `OK`<br>`"myvalue"` |
| **KEYS**             | `KEYS *`                                       | List of keys        |
| **TYPE**             | `TYPE mykey`                                   | `string`            |
| **DEL** / **UNLINK** | `DEL mykey`                                    | `(integer) 1`       |
| **EXPIRE**           | `SET session:1 "data"`<br>`EXPIRE session:1 5` | `OK`                |
| **RENAME**           | `SET a "x"`<br>`RENAME a b`<br>`GET b`         | `OK`<br>`"x"`       |

---
### 2. List Operations

| Command           | Example                                             | Expected Reply                   |
| ----------------- | --------------------------------------------------- | -------------------------------- |
| **LGET**          | `RPUSH L a b c`<br>`LGET L`                         | `1) "a"`<br>`2) "b"`<br>`3) "c"` |
| **LLEN**          | `LLEN L`                                            | `(integer) 3`                    |
| **LPUSH / RPUSH** | `LPUSH L "start"`<br>`RPUSH L "end"`                | `(integer) 4`<br>`(integer) 5`   |
| **LPOP / RPOP**   | `LPOP L`<br>`RPOP L`                                | `"start"`<br>`"end"`             |
| **LREM**          | `RPUSH L x y x z x`<br>`LREM L 2 x`<br>`LREM L 0 x` | `(integer) 2`<br>`(integer) <n>` |
| **LINDEX**        | `LINDEX L 1`<br>`LINDEX L -1`                       | `"y"`<br>`"z"`                   |
| **LSET**          | `LSET L 1 "new_val"`<br>`LINDEX L 1`                | `OK`<br>`"new_val"`              |

---
### 3. Hash Operations

| Command     | Example                                                       | Expected Reply                                                                              |
| ----------- | ------------------------------------------------------------- | ------------------------------------------------------------------------------------------- |
| **HSET**    | `HSET user:1 name Alice age 30 email a@x.com`                 | `(integer) 1` (per field)                                                                   |
| **HGET**    | `HGET user:1 email`                                           | `"a@x.com"`                                                                                 |
| **HEXISTS** | `HEXISTS user:1 address`<br>`HEXISTS user:1 name`             | `(integer) 0`<br>`(integer) 1`                                                              |
| **HDEL**    | `HDEL user:1 age`<br>`HEXISTS user:1 age`                     | `(integer) 1`<br>`(integer) 0`                                                              |
| **HLEN**    | `HLEN user:1`                                                 | `(integer) 2`                                                                               |
| **HKEYS**   | `HKEYS user:1`                                                | `1) "name"`<br>`2) "email"`                                                                 |
| **HVALS**   | `HVALS user:1`                                                | `1) "Alice"`<br>`2) "a@x.com"`                                                              |
| **HGETALL** | `HGETALL user:1`                                              | `1) "name"`<br>`2) "Alice"`<br>`3) "email"`<br>`4) "a@x.com"`                               |
| **HMSET**   | `HMSET user:2 name Bob age 25 city Paris`<br>`HGETALL user:2` | `OK`<br>`1) "name"`<br>`2) "Bob"`<br>`3) "age"`<br>`4) "25"`<br>`5) "city"`<br>`6) "Paris"` |

---

## 📝 References

* [Redis Official Documentation](https://redis.io/docs/)
* ["Build Your Own Redis"](https://build-your-own.org/redis/)

---
