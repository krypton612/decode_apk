#include "include/Menu.h"
#include <string>

Menu::Menu(std::string text, char trigger, std::string *items, int num_items) {

  this->text = text;
  this->trigger = trigger;

  this->num_items = num_items;
  this->items = items;
  this->selected_item = 0;
}

void Menu::selectNextItem() {
    selected_item++;
    if (selected_item >= num_items) 
      selected_item = 0;
    
  }
void Menu::selectPrevtItem() {
    selected_item--;
    if (selected_item < 0) 
      selected_item = num_items - 1;
    
}
Menu::~Menu(){}
