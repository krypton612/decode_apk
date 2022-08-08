#include "include/MenuBar.h"
#include "include/itemAPK.h"
#include <cstdlib>
#include <curses.h>
#include <string>
#include <algorithm>

MenuBar::MenuBar(WINDOW *win, Menu *menus,
                 int num_menus) // constructor de la clase menubar recibe la
                                // ventana actual recibe un objeto menu sad
{
  this->win = win;
  this->menus = menus;
  this->num_menus = num_menus;

  int yMax, xMax, yBeg, xBeg;
  int yMaxM, xMaxM, yBegM, xBegM;

  getmaxyx(win, yMax, xMax);
  getbegyx(win, yBeg, xBeg); // obtiene los valores iniciales de la ventana

  outputwin = newwin(yMax / 2 - 5, xMax - 2, (yMax / 2) + 5, xBeg + 1);
  menuwin = newwin(yMax / 2, xMax - 2, yBeg + 1, xBeg + 1);
  //   outputwindow = newwin((yMaxM/2)-2, xMaxM - 5, (yMaxM/2), xMaxM - 5);

  keypad(menuwin, true);
  box(outputwin, 0, 0);
  wrefresh(menuwin);
  int current_pos =
      2; // la distancia con la que inicia el primer caracter del menubar
  for (int i = 0; i < num_menus; i++) {
    this->menus[i].start_x = current_pos;
    current_pos += this->menus[i].text.length() +
                   3; // progresivamente va avanzando y tomando una nueva
                      // posicion para las nuevas opciones
  }
}
void MenuBar::reset() {
  for (int i = 0; i < num_menus; i++) {
    int start_x = menus[i].start_x;
    std::string text = menus[i].text;
    mvwprintw(win, 0, start_x, text.c_str());
  }
  wrefresh(win);
}

void MenuBar::draw() // esta funcion permite mostrar de manera directa el menu
                     // en WINDOW
{
  for (int i = 0; i < num_menus; i++) {
    drawMenu(menus[i], selected_menu == i);
  }
  selected_menu = -1;
}
void MenuBar::drawMenu(Menu menu, bool is_selected) {
  int start_x = menu.start_x;
  std::string text = menu.text;

  if (is_selected) // este condicional permite saber en que se selecciono y
                   // entonces permite manipularlo, canbiarlo de color por
                   // ejemplo
    wattron(win, A_STANDOUT);
  mvwprintw(win, 0, start_x, text.c_str());
  wattroff(win, A_STANDOUT);
  wrefresh(win);

  int ch;
  drawMenuItems(menu);
  wrefresh(menuwin);
  int yMax, xMax;
  getmaxyx(menuwin, yMax, xMax);

  while (is_selected && (ch = wgetch(menuwin))) {
    switch (ch) {
    case KEY_DOWN:
      menu.selectNextItem();
      break;
    case KEY_UP:
      menu.selectPrevtItem();
      break;
    case '\n':

      if (text == "[File apk]") {
        mvwprintw(this->win, yMax + yMax, 2,
                  menu.items[menu.selected_item]
                      .c_str()); // menu.text.c_str return titles
        item_selected_save(menu.items[menu.selected_item], ".apk");
        wrefresh(this->win);
      }
      if (text == "[File jar]") {
        mvwprintw(this->win, yMax + yMax, 70,
                  menu.items[menu.selected_item]
                      .c_str()); // menu.text.c_str return titles
        item_selected_save(menu.items[menu.selected_item], ".jar");

        wrefresh(this->win);
      }
      if (text == "[Actions]") {

        if (menu.items[menu.selected_item] ==
            "Extraer jar de apk seleccionado") {
          //*
          //  Aqui va el codigo para extraer el jar de un apk
          //
          // int y, x, bx, by;
          // getbegyx(outputwin, y, x);
          // mvwprintw(outputwin, 1, 2, "mierda");
          // wrefresh(outputwin);
          //std::string input;
          //int yMax, xMax, yBeg, xBeg;
          //move(yBeg + 1, xBeg + 1);
          // let the terminal do the line editing
          //nocbreak();
          //echo();

          // this reads from buffer after <ENTER>, not "raw"
          // // so any backspacing etc. has already been taken care of
          // int ch = getch();
          //
          // while (ch != '\n') {
          //   input.push_back(ch);
          //   ch = getch();
          // }
          // move(0, 4);
          // mvwprintw(outputwin, 1, 2, input.c_str());

          // restore your cbreak / echo settings here
          std::string command = "./bin/dex2jar/d2j-dex2jar.sh ";
          std::string cadena_de_apk = item_extrac_save(".apk");
          command = command + cadena_de_apk;
          std::string name_dir_file = getDir(cadena_de_apk);
          command = command + " -o jar_dir/"+name_dir_file + ".jar > /dev/null 2>&1";
          std::system(command.c_str());
          
          std::string message = "Ah sido generado un nuevo jar en la ruta jar_dir/"+name_dir_file+".jar";

          mvwprintw(outputwin, 3, 10, message.c_str());
          wrefresh(outputwin);
        }
        if (menu.items[menu.selected_item] == "Decodificar jar seleccionado") {
          //*
          //  Aqui va el codigo para decodificar el jar
          //
          std::string command = "java -jar bin/jd-cli.jar ";
          std::string cadena_de_jar = item_extrac_save(".jar");

          std::string name_dir_file = getDir(cadena_de_jar);
          
          command = command + cadena_de_jar + " -od output/"+name_dir_file+" > /dev/null 2>&1" ;

          std::system(command.c_str());
          std::string message = "Ah sido generado un nuevo directorio en la ruta output/"+name_dir_file;
          wrefresh(outputwin);
        }
      }
      if (text == "[Options]") {
        if (menu.items[menu.selected_item] ==
            "Salir") { // retorna un string y compara
          endwin();
          exit(1); // salir del programa
        }
      }

      break;
    default:
      is_selected = false;
      break;
    }
    drawMenuItems(menu);
  }

  werase(menuwin);
  wrefresh(menuwin);
  wrefresh(outputwin);

  reset();
}

void MenuBar::drawMenuItems(Menu menu) {

  int yMax, xMax;
  getmaxyx(menuwin, yMax, xMax);

  for (int i = 0; i < menu.num_items; i++) {
    mvwprintw(menuwin, i, 0, menu.items[i].c_str());

    if (menu.selected_item == i) {
      mvwchgat(menuwin, i, 0, xMax, A_NORMAL, 1, NULL);

    } else {
      mvwchgat(menuwin, i, 0, xMax, A_STANDOUT, 0, NULL);
    }
  }
}

void MenuBar::handlerTrigger(
    char trigger) // el escucha o handlerTrigger esta oyendo las
                  // teclas y una vez precionada controla esta
                  // alterando la clase y el objeto en tiempo real
{
  for (int i = 0; i < num_menus; i++) {
    if (trigger == this->menus[i].trigger) {
      selected_menu = i;
    }
  }
}
std::string MenuBar::getDir(std::string data_cadena) {
  std::string chars = ":/._";
  // for (int i = 0; i < data.length(); i++) 
  // {
  //   if (data[i] == '/' || data[i] == ':')
  //   {
  //     data[i] = '_';
  //   }
  //   else
  //   {
  //     data[i] = data[i];
  //   }
  // }
  // std::string command = "mkdir ";
  // std::string execute_comand = command + data;
  // std::system(execute_comand.c_str());
  // 
  //

    for (char c: chars) {

        data_cadena.erase(std::remove(data_cadena.begin(), data_cadena.end(), c), data_cadena.end());
    }
    
  return data_cadena;
}
