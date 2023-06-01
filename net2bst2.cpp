/*
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class ProgramaNetflix {
public:
  string id;
  string title;
  string type;
  string description;
  int release_year;
  string age_certification;
  int runtime;
  string genres;
  string production_countries;
  int seasons;
  string imdb_id;
  double imdb_score;
  int imdb_votes;
  double tmdb_popularity;
  double tmdb_score;

  ProgramaNetflix() {}

  ProgramaNetflix(const string &id, const string &title, const string &type,
                  const string &description, int release_year,
                  const string &age_certification, int runtime,
                  const string &genres, const string &production_countries,
                  int seasons, const string &imdb_id, double imdb_score,
                  int imdb_votes, double tmdb_popularity, double tmdb_score)
      : id(id), title(title), type(type), description(description),
        release_year(release_year), age_certification(age_certification),
        runtime(runtime), genres(genres),
        production_countries(production_countries), seasons(seasons),
        imdb_id(imdb_id), imdb_score(imdb_score), imdb_votes(imdb_votes),
        tmdb_popularity(tmdb_popularity), tmdb_score(tmdb_score) {}
};

class Node {
public:
  ProgramaNetflix data;
  Node *left;
  Node *right;

  Node(ProgramaNetflix value) : data(value), left(nullptr), right(nullptr) {}
};

class TreeBST {
private:
  // Node* root;

  Node *insertNode(Node *root, ProgramaNetflix data) {
    if (root == nullptr) {
      Node *newNode = new Node(data);
      return newNode;
    }
    if (data.id < root->data.id) {
      root->left = insertNode(root->left, data);
    } else if (data.id > root->data.id) {
      root->right = insertNode(root->right, data);
    }
    return root;
  }

  Node *searchNode(Node *root, string id) {
    if (root == nullptr || root->data.id == id) {
      return root;
    }
    if (id < root->data.id) {
      return searchNode(root->left, id);
    }
    return searchNode(root->right, id);
  }

  Node *findMinNode(Node *node) {
    Node *current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  Node *deleteNode(Node *root, string id) {
    if (root == nullptr) {
      return root;
    }
    if (id < root->data.id) {
      root->left = deleteNode(root->left, id);
    } else if (id > root->data.id) {
      root->right = deleteNode(root->right, id);
    } else {
      if (root->left == nullptr) {
        Node *temp = root->right;
        delete root;
        return temp;
      } else if (root->right == nullptr) {
        Node *temp = root->left;
        delete root;
        return temp;
      }
      Node *temp = findMinNode(root->right);
      root->data = temp->data;
      root->right = deleteNode(root->right, id);
    }
    return root;
  }

public:
  Node *root;
  Node *getRoot() const { return root; }
  TreeBST() : root(nullptr) {}

  void insert(ProgramaNetflix data) { root = insertNode(root, data); }

  void remove(string id) { root = deleteNode(root, id); }

  void search(string id) {
    Node *node = searchNode(root, id);
    if (node != nullptr) {
      printPrograma(node->data);
    } else {
      cout << "Program not found." << endl;
    }
  }

  void printPrograma(const ProgramaNetflix &programa) {
    cout << "ID: " << programa.id << endl;
    cout << "Title: " << programa.title << endl;
    cout << "Type: " << programa.type << endl;
    cout << "Description: " << programa.description << endl;
    cout << "Release Year: " << programa.release_year << endl;
    cout << "Age Certification: " << programa.age_certification << endl;
    cout << "Runtime: " << programa.runtime << endl;
    cout << "Genres: " << programa.genres << endl;
    cout << "Production Countries: " << programa.production_countries << endl;
    cout << "Seasons: " << programa.seasons << endl;
    cout << "IMDB ID: " << programa.imdb_id << endl;
    cout << "IMDB Score: " << programa.imdb_score << endl;
    cout << "IMDB Votes: " << programa.imdb_votes << endl;
    cout << "TMDB Popularity: " << programa.tmdb_popularity << endl;
    cout << "TMDB Score: " << programa.tmdb_score << endl;
  }
};

void loadFileData(TreeBST &bst) {
  ifstream file("titles8.csv");
  if (!file.is_open()) {
    cout << "Error opening file." << endl;
    return;
  }

  string line;
  getline(file, line); // Skip header line

  while (getline(file, line)) {
    stringstream ss(line);
    string field;
    vector<string> fields;

    while (getline(ss, field, ',')) {
      fields.push_back(field);
    }

    if (fields.size() == 15) {
      ProgramaNetflix programa(fields[0], fields[1], fields[2], fields[3],
                               stoi(fields[4]), fields[5], stoi(fields[6]),
                               fields[7], fields[8], stoi(fields[9]),
                               fields[10], stod(fields[11]), stoi(fields[12]),
                               stod(fields[13]), stod(fields[14]));
      bst.insert(programa);
    }
  }

  file.close();
}

void printMenu() {
  cout << "Menu:" << endl;
  cout << "1. Insert new program" << endl;
  cout << "2. Remove program" << endl;
  cout << "3. Search program" << endl;
  cout << "4. Search top 5" << endl;
  cout << "9. Exit" << endl;
}

ProgramaNetflix readProgramData() {
  ProgramaNetflix programa;

  cout << "ID: ";
  cin.ignore();
  getline(cin, programa.id);
  cout << "Title: ";
  getline(cin, programa.title);
  cout << "Type: ";
  getline(cin, programa.type);
  cout << "Description: ";
  getline(cin, programa.description);
  cout << "Release Year: ";
  cin >> programa.release_year;
  cout << "Age Certification: ";
  cin.ignore();
  getline(cin, programa.age_certification);
  cout << "Runtime: ";
  cin >> programa.runtime;
  cout << "Genres: ";
  cin.ignore();
  getline(cin, programa.genres);
  cout << "Production Countries: ";
  getline(cin, programa.production_countries);
  cout << "Seasons: ";
  cin >> programa.seasons;
  cout << "IMDB ID: ";
  cin.ignore();
  getline(cin, programa.imdb_id);
  cout << "IMDB Score: ";
  cin >> programa.imdb_score;
  cout << "IMDB Votes: ";
  cin >> programa.imdb_votes;
  cout << "TMDB Popularity: ";
  cin >> programa.tmdb_popularity;
  cout << "TMDB Score: ";
  cin >> programa.tmdb_score;

  return programa;
}

void showTopPrograms(TreeBST &bst, int releaseYear) {
  // Node* root = bst.getRoot();
  vector<ProgramaNetflix> topMovies;
  vector<ProgramaNetflix> topShows;

  // Fun�o auxiliar para percorrer a �rvore e encontrar os programas com maior
  // vota�o
  function<void(Node *)> findTopPrograms = [&](Node *node) {
    if (node == nullptr) {
      return;
    }

    findTopPrograms(node->left);

    if (node->data.release_year == releaseYear) {
      if (node->data.type == "MOVIE") {
        topMovies.push_back(node->data);
        sort(topMovies.begin(), topMovies.end(),
             [](const ProgramaNetflix &p1, const ProgramaNetflix &p2) {
               return p1.imdb_votes > p2.imdb_votes;
             });
        if (topMovies.size() > 5) {
          topMovies.pop_back();
        }
      } else if (node->data.type == "SHOW") {
        topShows.push_back(node->data);
        sort(topShows.begin(), topShows.end(),
             [](const ProgramaNetflix &p1, const ProgramaNetflix &p2) {
               return p1.imdb_votes > p2.imdb_votes;
             });
        if (topShows.size() > 5) {
          topShows.pop_back();
        }
      }
    }

    findTopPrograms(node->right);
  };

  findTopPrograms(bst.root);

  cout << "Top 5 MOVIES released in " << releaseYear
       << " with highest imdb_votes:" << endl;
  for (const auto &movie : topMovies) {
    cout << "ID: " << movie.id << " | Title: " << movie.title
         << " | imdb_votes: " << movie.imdb_votes << endl;
  }

  cout << endl;

  cout << "Top 5 SHOWS released in " << releaseYear
       << " with highest imdb_votes:" << endl;
  for (const auto &show : topShows) {
    cout << "ID: " << show.id << " | Title: " << show.title
         << " | imdb_votes: " << show.imdb_votes << endl;
  }
}

int main() {
  TreeBST bst;
  loadFileData(bst);

  int choice;
  while (true) {
    printMenu();
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      ProgramaNetflix programa = readProgramData();
      bst.insert(programa);
      break;
    }
    case 2: {
      string id;
      cout << "Enter the ID of the program to remove: ";
      cin.ignore();
      getline(cin, id);
      bst.remove(id);
      break;
    }
    case 3: {
      string id;
      cout << "Enter the ID of the program to search: ";
      cin.ignore();
      getline(cin, id);
      auto start = std::chrono::high_resolution_clock::now();
      bst.search(id);
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      std::cout << "A busca levou " << duration.count() << " milissegundos.\n";

      break;
    }

    case 4: {
      int releaseYear;
      cout << "Enter the release year to filter programs: ";
      cin >> releaseYear;
      // Node* root = bst.getRoot();
      // showTopPrograms(root, releaseYear);

      showTopPrograms(bst, releaseYear);
      break;
    }

    case 9: {
      return 0;
    }
    default:
      cout << "Invalid choice. Please try again." << endl;
    }
  }

  return 0;
}
*/