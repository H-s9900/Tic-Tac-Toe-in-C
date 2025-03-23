# 🎮 Tic-Tac-Toe Game

A simple yet fun Tic-Tac-Toe game built using **C and Raylib**! Play in **single-player (against AI)** or **two-player mode** and enjoy the classic strategy game. 🏆

---

## 📸 Screenshots

### 🏠 Main Menu
![image](https://github.com/user-attachments/assets/3eabeaaf-efb6-423f-851a-16d8b0f53d21)

### 🏆 Winning Screen
![image](https://github.com/user-attachments/assets/a5bf3575-dd53-427e-83fd-582ec4ef2af5)
![image](https://github.com/user-attachments/assets/c398aa22-a595-42cb-a4fe-005a98b42e84)

---

## 🚀 Features

✔️ Single-player mode with a basic AI 🤖\
✔️ Two-player mode for local multiplayer 🎭\
✔️ Score tracking for Player X, Player O, and Draws 📊\
✔️ Winning line animation 🏅\
✔️ Interactive main menu with mode selection 🎮

---

## 🛠 Installation & Setup

### 1️⃣ Install Dependencies

Make sure you have **Raylib** installed on your system.

- For Linux (Ubuntu/Debian):
  ```sh
  sudo apt install libraylib-dev
  ```
- For Windows:
  - Download and install Raylib from [raylib.com](https://www.raylib.com/)

### 2️⃣ Compile the Code

Run the following command to compile:

```sh
gcc test.c -o test -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

### 3️⃣ Run the Game

```sh
./test.exe
```

---

## 🎮 How to Play

1️⃣ **Launch the Game** - Start the program to enter the main menu.\
2️⃣ **Select Mode** - Choose between **Single Player** (against AI) or **Two Player** mode.\
3️⃣ **Gameplay** - Click on the grid to place your **X** or **O**. The first to get 3 in a row wins!\
4️⃣ **Winning Conditions** - The game detects row, column, and diagonal victories.\
5️⃣ **Restart or Exit** - After a match, click to play again or return to the menu.

---

## 🏗 Code Structure

📂 **Main Functions:**

- `DrawBoard()` → Draws the Tic-Tac-Toe grid.
- `DrawSymbols()` → Displays **X** and **O** on the board.
- `HandleClick()` → Handles user input and updates the board.
- `CheckWinner()` → Checks for a winner and triggers animations.
- `ComputerMove()` → AI logic for single-player mode.
- `DrawWinningLine()` → Highlights the winning line.
- `ResetGame()` → Resets the board for a new round.

---

## 🔧 Future Improvements

✨ **Better AI** with minimax algorithm 🤖\
✨ **Animated UI & Sound Effects** for better experience 🔊\
✨ **Online Multiplayer Mode** for remote play 🌍

---

## 📜 License

This project is **open-source**. Feel free to use, modify, and contribute! 🚀

---

Made with ❤️ by Sweety using **C & Raylib** 🎨🎮
