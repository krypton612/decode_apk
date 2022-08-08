#include <fstream>
#include <string>
#include <curses.h>

bool item_selected_save(std::string item_path_apk,std::string name) {
  std::ofstream fich{name, std::ios::out};
  if (!fich) {
    return false;
  } else {
    fich << item_path_apk;
    return true;
  }
}
std::string item_extrac_save(std::string name) {
  std::string data_recole;
  std::ifstream usuarios;
  usuarios.open(name, std::ios::in);
  while (!usuarios.eof()) {
    usuarios >> data_recole;
    if (!usuarios.eof()) {
      usuarios >> data_recole;
    }
  }
  usuarios.close();
  return data_recole;
}
