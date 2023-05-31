#ifndef __PROGRAMANETFLIX_H__
#define __PROGRAMANETFLIX_H__
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
};

#endif