#include "AVL.h"
#include "NodeAVL.h"
#include "ProgramaNetFlix.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<ProgramaNetFlix> readCsv(const std::string &filename) {
  std::vector<ProgramaNetFlix> programs;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Falha ao abrir o arquivo" << std::endl;
    return programs;
  }

  std::string line, word;
  std::getline(file, line);

  while (std::getline(file, line)) {
    std::istringstream s(line);
    std::vector<std::string> data;

    while (std::getline(s, word, ',')) {
      data.push_back(word);
    }

    if (data.size() >= 9) {
      std::vector<std::string> genres;
      std::istringstream genreStream(data[7]);
      std::string genre;
      while (std::getline(genreStream, genre, '\'')) {
        if (genre != "[" && genre != "]" && genre != ", ") {
          genres.push_back(genre);
        }
      }

      std::vector<std::string> countries;
      std::istringstream countryStream(data[8]);
      std::string country;
      while (std::getline(countryStream, country, '\'')) {
        if (country != "[" && country != "]" && country != ", ") {
          countries.push_back(country);
        }
      }

      ProgramaNetFlix program(
          data[0], data[1], data[2], data[3], std::atoi(data[4].c_str()),
          data[5], std::atoi(data[6].c_str()), genres, countries,
          std::atof(data[9].c_str()), data[10], std::atof(data[11].c_str()),
          std::atoi(data[12].c_str()), std::atof(data[13].c_str()),
          std::atof(data[14].c_str()));

      programs.push_back(program);
    }
  }

  return programs;
}

int main() {

  std::vector<ProgramaNetFlix> programs = readCsv("titles.csv");
  std::cout << programs.size() << std::endl;
  




  return 0;
}