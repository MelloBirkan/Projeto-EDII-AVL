#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class ProgramaNetFlix {
private:
  std::string id;
  std::string title;
  std::string type;
  std::string description;
  int release_year;
  std::string age_certification;
  int runtime;
  std::vector<std::string> genres;
  std::vector<std::string> production_countries;
  float seasons;
  std::string imdb_id;
  float imdb_score;
  int imdb_votes;
  float tmdb_popularity;
  float tmdb_score;

public:
  // Constructor
  ProgramaNetFlix(std::string id, std::string title, std::string type,
                  std::string description, int release_year,
                  std::string age_certification, int runtime,
                  std::vector<std::string> genres,
                  std::vector<std::string> production_countries, float seasons,
                  std::string imdb_id, float imdb_score, int imdb_votes,
                  float tmdb_popularity, float tmdb_score)
      : id(id), title(title), type(type), description(description),
        release_year(release_year), age_certification(age_certification),
        runtime(runtime), genres(genres),
        production_countries(production_countries), seasons(seasons),
        imdb_id(imdb_id), imdb_score(imdb_score), imdb_votes(imdb_votes),
        tmdb_popularity(tmdb_popularity), tmdb_score(tmdb_score) {}

  // Getters
  std::string getId() { return id; }
  std::string getTitle() { return title; }
  std::string getType() { return type; }
  std::string getDescription() { return description; }
  int getReleaseYear() { return release_year; }
  std::string getAgeCertification() { return age_certification; }
  int getRuntime() { return runtime; }
  std::vector<std::string> getGenres() { return genres; }
  std::vector<std::string> getProductionCountries() {
    return production_countries;
  }
  float getSeasons() { return seasons; }
  std::string getImdbId() { return imdb_id; }
  float getImdbScore() { return imdb_score; }
  int getImdbVotes() { return imdb_votes; }
  float getTmdbPopularity() { return tmdb_popularity; }
  float getTmdbScore() { return tmdb_score; }

  // Setters
  void setId(std::string id) { this->id = id; }
  void setTitle(std::string title) { this->title = title; }
  void setType(std::string type) { this->type = type; }
  void setDescription(std::string description) {
    this->description = description;
  }
  void setReleaseYear(int release_year) { this->release_year = release_year; }
  void setAgeCertification(std::string age_certification) {
    this->age_certification = age_certification;
  }
  void setRuntime(int runtime) { this->runtime = runtime; }
  void setGenres(std::vector<std::string> genres) { this->genres = genres; }
  void setProductionCountries(std::vector<std::string> production_countries) {
    this->production_countries = production_countries;
  }
  void setSeasons(float seasons) { this->seasons = seasons; }
  void setImdbId(std::string imdb_id) { this->imdb_id = imdb_id; }
  void setImdbScore(float imdb_score) { this->imdb_score = imdb_score; }
  void setImdbVotes(int imdb_votes) { this->imdb_votes = imdb_votes; }
  void setTmdbPopularity(float tmdb_popularity) {
    this->tmdb_popularity = tmdb_popularity;
  }
  void setTmdbScore(float tmdb_score) { this->tmdb_score = tmdb_score; }
};

std::vector<ProgramaNetFlix> readCsv(const std::string &filename) {
  std::vector<ProgramaNetFlix> programs;
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Failed to open file" << std::endl;
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


    if (data.size() == 15) {

      ProgramaNetFlix program(
          data[0], data[1], data[2], data[3], std::stoi(data[4]), data[5],
          std::stoi(data[6]), {data[7]}, {data[8]}, std::stof(data[9]),
          data[10], std::stof(data[11]), std::stoi(data[12]),
          std::stof(data[13]), std::stof(data[14]));

      programs.push_back(program);
    }
  }

  return programs;
}

int main() {

  std::vector<ProgramaNetFlix> programs = readCsv("titles.csv");

  return 0;
}