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
};
   
class Node {
public:
    ProgramaNetFlix data;
    int height;
    Node* left;
    Node* right;

    Node(ProgramaNetFlix data)
        : data(data), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node);
    int getBalanceFactor(Node* node);
    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* insertNode(Node* node, ProgramaNetFlix data);

public:
    AVLTree() : root(nullptr) {}
    void insert(ProgramaNetFlix data);
};

int AVLTree::getHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    Node* subtree = newRoot->left;

    newRoot->left = node;
    node->right = subtree;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}



Node* findMinNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}



Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    Node* subtree = newRoot->right;

    newRoot->right = node;
    node->left = subtree;

    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = std::max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

    return newRoot;
}

Node* AVLTree::insertNode(Node* node, ProgramaNetFlix data) {
    if (node == nullptr) {
        return new Node(data);
    }

    if (data.getId() < node->data.getId()) {
        node->left = insertNode(node->left, data);
    } else if (data.getId() > node->data.getId()) {
        node->right = insertNode(node->right, data);
    } else {
        // Handle case where the node already exists (if needed)
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (data.getId() < node->left->data.getId()) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (balanceFactor < -1) {
        if (data.getId() > node->right->data.getId()) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }

    return node;
}

void AVLTree::insert(ProgramaNetFlix data) {
    root = insertNode(root, data);
}

std::vector<ProgramaNetFlix> readCsv(const std::string& filename) {
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
  int count = 0;
  AVLTree avl;
  for (auto &program : programs) {
    std::cout << "Inserindo " << program.getId() << std::endl;
    avl.insert(program);
    count++;
  }

  std::cout << "Total de programas inseridos: " << count << std::endl;
  return 0;
}