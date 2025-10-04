# TinyWebServer-C

A minimal HTTP web server written in C. It listens on port 8080 and responds with a simple HTML page.

## How It Works

- The server creates a TCP socket, binds it to port 8080, and listens for incoming connections.
- When a client connects (e.g., a browser or `curl`), the server reads the request and responds with a fixed HTML message:  
  `<h1>Hello, world!</h1>`
- The server runs in an infinite loop, handling one connection at a time.

## Files

- `main.c`: Contains the entry point and the `launch` function that handles HTTP requests.
- `server.c` / `server.h`: Implements the server setup and configuration.

## How to Build and Run

1. **Clone or download the repository.**
2. **Open a terminal in the project directory.**
3. **Compile the code:**
   ```bash
   gcc main.c server.c -o tinywebserver
   ```
4. **Run the server:**
   ```bash
   ./tinywebserver
   ```
5. **Open your browser and go to:**
   ```
   http://127.0.0.1:8080/
   ```
   Or use curl:
   ```bash
   curl http://127.0.0.1:8080/
   ```

## Example Output

You should see:

```html
<!DOCTYPE html><html><body><h1>Hello, world!</h1></body></html>
```

## Notes

- The server only handles one connection at a time and always returns the same HTML page.
- Make sure port 8080 is not in use by another application.
- To stop the server, press `Ctrl+C` in the terminal.