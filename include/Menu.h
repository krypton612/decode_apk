#include <curses.h>
#include <string>

class Menu {
public:
  Menu(std::string text, char trigger, std::string *items, int num_items);
  Menu(Menu &&) = default;
  Menu(const Menu &) = default;
  Menu &operator=(Menu &&) = default;
  Menu &operator=(const Menu &) = default;
  ~Menu();
  void selectNextItem();
  void selectPrevtItem();

public:
  int start_x;
  std::string text;
  char trigger; // caracter de escucha
                //
  std::string *items;
  int num_items;
  int selected_item;
  std::string selected_string = " ";

};
