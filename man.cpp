#include <cstdlib>
#include <iostream>
#include <algorithm>

std::string getDir(std::string data_cadena) {
  std::string chars = ":/";
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
