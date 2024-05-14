//NOTE: icons:   

#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <chrono>
#include <ostream>
#include <sstream>
#include <thread>
#include <csignal>
#include <SFML/Audio.hpp>
#include <termios.h>
#include <strstream>


auto disable_keyboard_input() -> void;
auto enable_keyboard_input() -> void;
auto set_term_settings() -> void;
auto cdoro() -> void;
auto short_break(size_t duration) -> void;
auto long_break(size_t duration) -> void;
auto cycle(size_t session_duration, size_t number_of_ss) -> void;
auto intro() -> void;

int main() {
  cdoro();
}

void disable_keyboard_input() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
  // Flush input buffer
  tcflush(STDIN_FILENO, TCIFLUSH);
}

void enable_keyboard_input() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= (ICANON | ECHO);  // Re-enable canonical mode and echoing
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Terminal

auto set_term_settings() -> void {
  std::cout << "\e[?25l"; // Hide cursor.
  disable_keyboard_input();
}
auto dis_term_settings() -> void {
  enable_keyboard_input();
  // Restore cursor visibility before exiting
  std::cout << "\e[?25h" << std::flush;
}

// Signal handler function
auto signal_handler(int signum) -> void {
  // Restore cursor visibility before exiting
  std::cout << "\e[?25h" << std::endl;
  enable_keyboard_input();
  exit(signum);
}

auto play_reminder() -> void {
  sf::Sound sound;
  sf::SoundBuffer buffer;
  std::stringstream buffer_path;

  buffer_path << getenv("HOME") << "/.cdoro/bell.mp3";

  buffer.loadFromFile(buffer_path.str());
  sound.setBuffer(buffer);
  sound.play();
  sound.setRelativeToListener(true);
  while (sound.getStatus() == sf::Sound::Status::Playing);
}

auto press(bool go_back) -> void {
  dis_term_settings();
  std::cout << "Press enter to start: ";
  std::getchar();
  std::cout << "\e[F\e[K";
  set_term_settings();
}

auto cycle(size_t session_duration, size_t number_of_ss) -> void {
  int session_id = 1;

  set_term_settings();
  while (session_id < 4) {
    int seconds = 0;
    int minutes = session_duration;

    std::cout << " Time left of session " << session_id << "/" << number_of_ss << std::endl;
    press(true);
    while (minutes != -1) {
      while (seconds != 0) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        --seconds;
        std::cout << "\r" << std::setw(2) << std::setfill('0') << minutes << ":"
          << std::setw(2) << std::setfill('0') << seconds << "  "
          << std::flush;
      }
      seconds = 60;
      --minutes;
    }

    ++session_id;
    std::cout << std::endl;

    system("notify-send \"a session ended\"");
    play_reminder();
    if (session_id != number_of_ss)
      short_break(1);
    else
      long_break(1);
  }
  dis_term_settings();
}


auto long_break(size_t duration) -> void {
  int seconds = 0;

  std::cout << " Long break " << std::endl;
  press(true);
  while (duration != -1) {
    while (seconds != 0) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      --seconds;
      std::cout << "\r" << std::setw(2) << std::setfill('0') << duration << ":"
        << std::setw(2) << std::setfill('0') << seconds << "  "
        << std::flush;
    }
    seconds = 60;
    --duration;
  }
  std::cout << std::endl;

  system("notify-send \"Go back!\"");
  play_reminder();
}

auto short_break(size_t duration) -> void {
  int seconds = 0;

  std::cout << " Short break " << std::endl;
  system("notify-send -t 20000 \"Rest when you're weary. Refresh and renew yourself, your body, your mind, your spirit. Then get back to work. - Ralph Marston\"");
  press(true);
  while (duration != -1) {
    while (seconds != 0) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      --seconds;
      std::cout << "\r" << std::setw(2) << std::setfill('0') << duration << ":"
        << std::setw(2) << std::setfill('0') << seconds << "  "
        << std::flush;
    }
    seconds = 60;
    --duration;
  }
  std::cout << std::endl;

  system("notify-send -t 20000 \"Don't watch the clock; do what it does. Keep going. - Sam Levenson\"");
  play_reminder();
}

auto intro() -> void {
  // Ask if wanna specific number of cycles of infinite
}

auto cdoro() -> void {
  // Install signal handler
  signal(SIGINT, signal_handler);

  set_term_settings();
  system("clear");
  intro();
  int cycle_id = 1;

  while (1) {
    system("clear");
    std::cout << "➜ cdoro ]" << cycle_id << ";+ [" << std::endl;
    cycle(1, 4);
    ++cycle_id;
  }
  dis_term_settings();
}

