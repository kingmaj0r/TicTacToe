# Tic-Tac-Toe with GTKmm (C++)

This is a simple Tic-Tac-Toe game implemented in C++ using **GTKmm** (C++ bindings for GTK). The game allows a player to compete against an AI that uses the **Minimax algorithm** for optimal play.

## Prerequisites:
- **GTKmm** version 3.x (C++ bindings for GTK)
- A C++ compiler that supports C++17 or later

### Installation
#### On Linux:
1. Install dependencies:
   - Ubuntu/Debian:
     ```bash
     sudo apt install libgtkmm-3.0-dev build-essential meson ninja-build
     ```
   - Fedora:
     ```bash
     sudo dnf install gtkmm30-devel gcc-c++ make meson ninja-build
     ```

2. Clone the repository:
    ```bash
    git clone https://github.com/KingMaj0r/TicTacToe.git
    cd TicTacToe
    ```

3. **Meson Build Setup**:
   set up the project:
   ```bash
   meson setup build
   ```

4. Build the project:
   ```bash
   meson compile -C build
   ```

5. Run the application:
   ```bash
   ./build/TicTacToe
   ```

## How It Works:
- The game creates a simple **3x3 grid** using GTK buttons. Each button represents a cell on the Tic-Tac-Toe board.
- The player clicks on any empty cell to place their mark ('X').
- The AI automatically makes its move by selecting the best possible move based on the **Minimax algorithm**.
- After each move, the game checks if there's a winner, and a message is shown for a win, loss, or draw.
- The game resets automatically after the result.

### **Minimax Algorithm**:
The AI uses **Minimax**, a decision-making algorithm that simulates all possible moves and selects the move that maximizes its chances of winning while minimizing the player’s chances.

- If the AI can win in a move, it will do so.
- If the player can win, it will block that move.
- Otherwise, it evaluates the best move using a depth-first search.

## License:
This project is open-source and available under the MIT License.
