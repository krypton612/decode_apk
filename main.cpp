#include "include/MenuBar.h"
#include "include/pathstring.h"
#include <cstdlib>
#include <dirent.h>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using std::getenv;

FILE *popen(const char *command, const char *mode);
int pclose(FILE *stream);

int checkIfFileExists(const char *filename) {
  struct stat buffer;
  int exist = stat(filename, &buffer);
  if (exist == 0)
    return 1;
  else
    return 0;
}

std::string pipe_to_string(const char *command) {
  FILE *file = popen(command, "r");

  if (file) {
    std::ostringstream stm;

    constexpr std::size_t MAX_LINE_SZ = 1024;
    char line[MAX_LINE_SZ];

    while (fgets(line, MAX_LINE_SZ, file))
      stm << line << '\n';

    pclose(file);
    return stm.str();
  }

  return "";
}

int size_dirs(int dat) {
  size_t count = 0;
  struct dirent *res;
  struct stat sb;

  const char *path;
  char *tmp = getenv(ENV_VAR);

  if (dat) {
    // your input path to apks
    path = "apk_dir";
    strcat(tmp, path);

  } else {
    // your input path to jars
    path = "jar_dir";
    strcat(tmp, path);
  }

  if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    DIR *folder = opendir(path);

    if (access(path, F_OK) != -1) {
      if (folder) {
        while ((res = readdir(folder))) {
          if (strcmp(res->d_name, ".") && strcmp(res->d_name, "..")) {
            count++;
          }
        }

        closedir(folder);
      } else {
        perror("Could not open the directory");
        exit(EXIT_FAILURE);
      }
    }

  } else {
    printf("The %s it cannot be opened or is not a directory\n", path);
    exit(EXIT_FAILURE);
  }

  return count;
}

std::string *MultiplyArrayByTwo(std::string arr[], int size, std::string path) {
  int i = 0;
  for (const auto &file : std::filesystem::directory_iterator(path)) {
    arr[i] = file.path().string() + "\n";
    i += 1;
  }

  return arr;
}

int main(int argc, char *argv[]) {
  // input your paths, recuerda debe ser igual al de arriba apk para las apk,
  // jar para los jar
  std::string path_apk = extract("apk_dir");

  std::string path_jar = extract("jar_dir");

  initscr();
  noecho();
  curs_set(0);

  if (!has_colors()) {
    return -1;
  }

  start_color();

  init_pair(1, COLOR_WHITE, COLOR_RED);
  init_pair(2, COLOR_BLACK, COLOR_RED);

  int windY, windX;

  getmaxyx(stdscr, windY, windX);

  WINDOW *win1 = newwin(windY - 1, windX - 1, 1, 1);
  box(win1, 0, 0);

  std::string c_array[40];
  std::string c_array2[40];

  std::string *menu1 =
      MultiplyArrayByTwo(c_array, c_array->length() + 1, path_apk);
  std::string *menu2 =
      MultiplyArrayByTwo(c_array2, c_array2->length() + 1, path_jar);
  std::string menu3[] = {"Extraer jar de apk seleccionado",
                         "Decodificar jar seleccionado"};
  std::string menu4[] = {"Instalar dependencias [jd-cli, dex2jar]","Verificar dependencias", "Salir"};

  Menu menus[4] = {

      Menu("[File apk]", 'q', menu1, size_dirs(1)),
      Menu("[File jar]", 'w', menu2, size_dirs(0)),
      Menu("[Actions]", 'e', menu3, 2),
      Menu("[Options]", 'r', menu4, 3),
  };

  MenuBar menubar = MenuBar(win1, menus, 4);
  menubar.draw();

  char ch; // para almacenar el caracter que se clickeo
           //

  // wgetch devuel true y la tecla que se preciono
  while (ch = wgetch(win1)) {
    menubar.handlerTrigger(ch);
    menubar.draw();
  }

  endwin();
  return 0;
}
