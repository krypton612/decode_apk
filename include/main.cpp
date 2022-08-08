#include <iostream>
#include "itemAPK.h"

int main (int argc, char *argv[])
{
  item_selected_save("/home/krypton612/a.out");
  std::string data = item_extrac_save();
  std::cout << "data decode is : "<< data << std::endl;
  item_selected_save("hola");
  data = item_extrac_save();
  std::cout << "data change in : "<< data << std::endl;
  return 0;
}
