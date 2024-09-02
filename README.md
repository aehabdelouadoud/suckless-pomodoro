![image](https://github.com/horanmustaplot/cdoro-pomodoro/assets/152083466/01c7afca-586e-414b-b994-6de22950efb7)


# cdoro Pomodoro

cdoro Pomodoro is a simple and efficient Pomodoro timer written in C++. The Pomodoro Technique is a time management method that uses a timer to break work into intervals, traditionally 25 minutes in length, separated by short breaks.

## Features

- Configurable work and break intervals
- Visual and auditory notifications
- Simple command-line interface

## Requirements

- C++ compiler
  - You're varorite C++ compiler, but please change it in the make file, cause by default I'm using GCC compiler.
- Libraries
  - sfml(for the notificaton sound)
- Notifications
  - notify-send(for push notifications)

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/horanmustaplot/cdoro-pomodoro.git
    ```

2. Navigate to the project directory:
    ```bash
    cd cdoro-pomodoro
    ```

3. Compile the code and install it:
    ```bash
    make install
    ```

## Usage

Run the compiled executable:
```bash
cdoro
