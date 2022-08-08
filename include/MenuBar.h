#include <iostream>
#include <string>
#include <curses.h>
#include "Menu.h"

class MenuBar
{
public:
  MenuBar(WINDOW *win, Menu *menus, int num_menus);
  MenuBar(MenuBar &&) = default;
  MenuBar(const MenuBar &) = default;
  MenuBar &operator=(MenuBar &&) = default;
  MenuBar &operator=(const MenuBar &) = default;

  void reset();
  void draw();
  void drawMenu(Menu menu, bool is_selected);
  void drawMenuItems(Menu menu);
  void handlerTrigger(char trigger);
  std::string getDir(std::string data_cadena);

public:
  WINDOW *menuwin;
  WINDOW *outputwin;
  WINDOW *win;

  Menu *menus;
  int num_menus;
  int selected_menu;
  std::string jar_name = "";
};

