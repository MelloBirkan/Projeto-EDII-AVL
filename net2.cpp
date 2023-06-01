#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Classe que representa um programa do Netflix
class ProgramaNetFlix {
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
  float imdb_score;
  int imdb_votes;
  float tmdb_popularity;
  float tmdb_score;
};

// N� da �rvore AVL
class Node {
public:
  ProgramaNetFlix data;
  Node *left;
  Node *right;
  int height;
};

// Classe que representa a �rvore AVL
class TreeAVL {
public:
  Node *root;

  // Construtor
  TreeAVL() { root = nullptr; }

  // Retorna a altura de um n�
  int getHeight(Node *node) {
    if (node == nullptr)
      return 0;
    return node->height;
  }

  // Retorna o fator de balanceamento de um n�
  int getBalance(Node *node) {
    if (node == nullptr)
      return 0;
    return getHeight(node->left) - getHeight(node->right);
  }

  // Atualiza a altura de um n�
  void updateHeight(Node *node) {
    if (node == nullptr)
      return;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
  }

  // Rotaciona para a direita em torno de um n�
  Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
  }

  // Rotaciona para a esquerda em torno de um n�
  Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
  }

  // Insere um programa na �rvore
  Node *insert(Node *node, ProgramaNetFlix data) {
    if (node == nullptr) {
      Node *newNode = new Node();
      newNode->data = data;
      newNode->left = nullptr;
      newNode->right = nullptr;
      newNode->height = 1;
      return newNode;
    }

    if (data.id < node->data.id)
      node->left = insert(node->left, data);
    else if (data.id > node->data.id)
      node->right = insert(node->right, data);
    else
      return node; // N�o permitir chaves duplicadas

    updateHeight(node);

    int balance = getBalance(node);

    // Rota�es para balancear a �rvore
    if (balance > 1 && data.id < node->left->data.id)
      return rotateRight(node);

    if (balance < -1 && data.id > node->right->data.id)
      return rotateLeft(node);

    if (balance > 1 && data.id > node->left->data.id) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }

    if (balance < -1 && data.id < node->right->data.id) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }

    return node;
  }

  // Busca um programa na �rvore pelo ID
  Node *search(Node *node, const string &id) {
    if (node == nullptr || node->data.id == id)
      return node;

    if (id < node->data.id)
      return search(node->left, id);

    return search(node->right, id);
  }

  // Encontra o n� com o menor valor (menor ID) na �rvore
  Node *findMinValueNode(Node *node) {
    Node *current = node;
    while (current->left != nullptr)
      current = current->left;
    return current;
  }

  // Remove um programa da �rvore
  Node *remove(Node *node, const string &id) {
    if (node == nullptr)
      return node;

    if (id < node->data.id)
      node->left = remove(node->left, id);
    else if (id > node->data.id)
      node->right = remove(node->right, id);
    else {
      if (node->left == nullptr || node->right == nullptr) {
        Node *temp = node->left ? node->left : node->right;
        if (temp == nullptr) {
          temp = node;
          node = nullptr;
        } else {
          *node = *temp;
        }
        delete temp;
      } else {
        Node *temp = findMinValueNode(node->right);
        node->data = temp->data;
        node->right = remove(node->right, temp->data.id);
      }
    }

    if (node == nullptr)
      return node;

    updateHeight(node);

    int balance = getBalance(node);

    // Rota�es para balancear a aTrvore
    if (balance > 1 && getBalance(node->left) >= 0)
      return rotateRight(node);

    if (balance > 1 && getBalance(node->left) < 0) {
      node->left = rotateLeft(node->left);
      return rotateRight(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
      return rotateLeft(node);

    if (balance < -1 && getBalance(node->right) > 0) {
      node->right = rotateRight(node->right);
      return rotateLeft(node);
    }

    return node;
  }

  // Fun�o auxiliar para imprimir os programas em ordem crescente de ID
  void printInOrder(Node *node) {
    if (node == nullptr)
      return;

    printInOrder(node->left);
    cout << "ID: " << node->data.id << ", Title: " << node->data.title << endl;
    printInOrder(node->right);
  }
};

// Fun�o auxiliar para converter uma string em um valor inteiro
int stoiWithDefault(const string &str, int defaultValue) {
  try {
    return stoi(str);
  } catch (const std::exception &) {
    return defaultValue;
  }
}

// Fun�o para ler o arquivo CSV e criar a �rvore AVL
void readCSVFile(TreeAVL &tree) {
  ifstream file("titles8.csv");
  if (!file.is_open()) {
    cout << "Erro ao abrir o arquivo titles.csv" << endl;
    return;
  }

  string line;
  getline(file, line); // Ignorar a primeira linha (cabe�alho)

  while (getline(file, line)) {
    stringstream ss(line);
    string item;

    ProgramaNetFlix programa;

    getline(ss, item, ',');
    programa.id = item;

    getline(ss, item, ',');
    programa.title = item;

    getline(ss, item, ',');
    programa.type = item;

    getline(ss, item, ',');
    programa.description = item;

    getline(ss, item, ',');
    programa.release_year = stoiWithDefault(item, 0);

    getline(ss, item, ',');
    programa.age_certification = item;

    getline(ss, item, ',');
    programa.runtime = stoiWithDefault(item, 0);

    getline(ss, item, ',');
    programa.genres = item;

    getline(ss, item, ',');
    programa.production_countries = item;

    getline(ss, item, ',');
    programa.seasons = stoiWithDefault(item, 0);

    getline(ss, item, ',');
    programa.imdb_id = item;

    getline(ss, item, ',');
    programa.imdb_score =
        item == "nd" ? 0.0 : std::strtod(item.c_str(), nullptr);

    getline(ss, item, ',');
    programa.imdb_votes = stoiWithDefault(item, 0);

    getline(ss, item, ',');
    programa.tmdb_popularity =
        item == "nd" ? 0.0 : std::strtod(item.c_str(), nullptr);

    getline(ss, item, ',');
    programa.tmdb_score =
        item == "nd" ? 0.0 : std::strtod(item.c_str(), nullptr);

    tree.root = tree.insert(tree.root, programa);
  }

  file.close();
}

bool compareVotes(const ProgramaNetFlix &program1,
                  const ProgramaNetFlix &program2) {
  return program1.imdb_score > program2.imdb_score;
}

// Função para dividir uma string em várias substrings usando um delimitador
vector<string> split(const string &str, char delimiter) {
  vector<string> result;
  stringstream ss(str);
  string item;
  while (getline(ss, item, delimiter)) {
    result.push_back(item);
  }
  return result;
}

// Função para analisar os programas por gênero
void analyzeByGenre(TreeAVL &tree) {
  unordered_map<string, vector<ProgramaNetFlix>> programsByGenre;

  // Função auxiliar para percorrer a árvore e adicionar os programas ao mapa
  function<void(Node *)> addPrograms = [&](Node *node) {
    if (node == nullptr)
      return;

    addPrograms(node->left);

    vector<string> genres = split(node->data.genres, ',');
    for (const string &genre : genres) {
      programsByGenre[genre].push_back(node->data);
    }

    addPrograms(node->right);
  };

  // Chama a função auxiliar para adicionar os programas ao mapa
  addPrograms(tree.root);

  // Agora, você pode analisar os dados do mapa. Por exemplo, vamos imprimir o
  // número total de programas de cada gênero:
  for (const auto &pair : programsByGenre) {
    if (pair.second.size() > 60)
      cout << "Genre: " << pair.first
           << ", Total Programs: " << pair.second.size() << endl;
  }
}

void mostWatchedProgramByGenre(TreeAVL &tree) {
  // Mapas para armazenar o programa mais assistido por gênero
  std::map<string, Node *> mostWatched;

  // Função auxiliar para percorrer a árvore e analisar os gêneros
  function<void(Node *)> analyze = [&](Node *node) {
    if (node == nullptr)
      return;

    analyze(node->left);

    // Se o programa atual tem mais visualizações do que o programa mais
    // assistido do mesmo gênero
    if (mostWatched[node->data.genres] == nullptr ||
        node->data.imdb_votes > mostWatched[node->data.genres]->data.imdb_votes)
      mostWatched[node->data.genres] = node;

    analyze(node->right);
  };

  // Chama a função auxiliar para analisar os gêneros
  analyze(tree.root);

  // Agora, podemos imprimir o programa mais assistido por gênero
  for (const auto &pair : mostWatched) {
    if (pair.second->data.imdb_votes > 500000) {
      cout << "Programa Mais Assistido: " << pair.second->data.title
           << ", Visualizações: " << pair.second->data.imdb_votes << endl;
    }
  }
}

void analyzeDuration(TreeAVL &tree) {
  int sum = 0;    // soma das durações
  int min = 9999; // duração mínima
  int max = 0;    // duração máxima
  int count = 0;  // número de programas

  // Função auxiliar para percorrer a árvore e analisar as durações
  function<void(Node *)> analyze = [&](Node *node) {
    if (node == nullptr)
      return;

    analyze(node->left);

    sum += node->data.runtime;
    min = std::min(min, node->data.runtime);
    max = std::max(max, node->data.runtime);
    count++;

    analyze(node->right);
  };

  // Chama a função auxiliar para analisar as durações
  analyze(tree.root);

  // Agora, podemos calcular e imprimir a duração média, mínima e máxima
  double average = static_cast<double>(sum) / count;
  cout << "duração média: " << max / 60 << " horas" << endl;
}

void findTopRatedPrograms(TreeAVL &tree, int year) {
  vector<ProgramaNetFlix> movies;
  vector<ProgramaNetFlix> shows;

  // Fun�o auxiliar para percorrer a �rvore e encontrar programas do ano
  // especificado
  function<void(Node *)> findPrograms = [&](Node *node) {
    if (node == nullptr)
      return;

    findPrograms(node->left);

    if (node->data.release_year == year) {
      if (node->data.type == "MOVIE") {
        movies.push_back(node->data);
      } else if (node->data.type == "SHOW") {
        shows.push_back(node->data);
      }
    }

    findPrograms(node->right);
  };

  // Chama a fun�o auxiliar para encontrar programas do ano especificado
  findPrograms(tree.root);

  // Ordena os programas com base nos votos usando a fun�o compareVotes
  sort(movies.begin(), movies.end(), compareVotes);
  sort(shows.begin(), shows.end(), compareVotes);

  // Imprime os 5 programas mais votados de cada tipo
  cout << "Top 5 Movies:" << endl;
  for (int i = 0; i < min(5, static_cast<int>(movies.size())); i++) {
    cout << "Titulo: " << movies[i].title << ", Nota: " << movies[i].imdb_score
         << endl;
  }

  cout << "Top 5 Shows Mais Votados:" << endl;
  for (int i = 0; i < min(5, static_cast<int>(shows.size())); i++) {
    cout << "Title: " << shows[i].title << ", Votes: " << shows[i].imdb_votes
         << endl;
  }
}

void analyzeLaunchYear(TreeAVL &tree) {
  // Mapa para armazenar a contagem de programas lançados em cada ano
  std::map<int, int> yearCounts;

  // Função auxiliar para percorrer a árvore e analisar os anos de lançamento
  function<void(Node *)> analyze = [&](Node *node) {
    if (node == nullptr)
      return;

    analyze(node->left);

    yearCounts[node->data.release_year]++;

    analyze(node->right);
  };

  // Chama a função auxiliar para analisar os anos de lançamento
  analyze(tree.root);

  // Agora, podemos imprimir a contagem de programas lançados em cada ano
  for (const auto &pair : yearCounts) {
    if (pair.first > 2000)
      cout << "Year: " << pair.first << ", Count: " << pair.second << endl;
  }
}

bool temNumero(const std::string &texto) {
  for (char c : texto) {
    if (isdigit(c)) {
      return true;
    }
  }
  return false;
}

void analyzeProductionCountry(TreeAVL &tree) {
  // Mapa para armazenar a contagem de programas para cada país
  std::map<string, int> countryCounts;

  // Função auxiliar para percorrer a árvore e analisar os países
  function<void(Node *)> analyze = [&](Node *node) {
    if (node == nullptr)
      return;

    analyze(node->left);

    countryCounts[node->data.production_countries]++;

    analyze(node->right);
  };

  // Chama a função auxiliar para analisar os países
  analyze(tree.root);

  // Agora, podemos imprimir a contagem de programas para cada país
  for (const auto &pair : countryCounts) {
    if (pair.first.length() == 3 && temNumero(pair.first) == false &&
        pair.second >= 37)
      cout << "País: " << pair.first << ", Contagem: " << pair.second << endl;
    if (pair.first == "BR.")
      cout << "País: " << pair.first << ", Contagem: " << pair.second << endl;
  }
}

int main() {
  TreeAVL tree;
  readCSVFile(tree);

  int choice;
  int id;

  while (true) {

    cout << "Menu:" << endl;
    cout << "1. Inserir um programa" << endl;
    cout << "2. Remover um programa" << endl;
    cout << "3. Buscar um programa" << endl;
    cout << "4. Buscar 5 melhores por ano" << endl;
    cout << "5. Programas mais assitidos de julho/2022" << endl;
    cout << "6. Ver analise sobre duração" << endl;
    cout << "7. Ver analise sobre quantidade de programas lancados nos anos"
         << endl;
    cout << "8. Ver analise sobre 5 principais paises produtores" << endl;
    cout << "9. Sair" << endl;
    cout << "Escolha uma opcao: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      ProgramaNetFlix programa;
      cout << "Informe os dados do programa:" << endl;
      cout << "ID: ";
      cin >> programa.id;
      cin.ignore(); // Ignorar o caractere de nova linha
      cout << "Title: ";
      getline(cin, programa.title);
      tree.root = tree.insert(tree.root, programa);
      cout << "Programa inserido com sucesso!" << endl;
    } break;
    case 2: {
      string id;
      cout << "Informe o ID do programa a ser removido: ";
      cin >> id;
      tree.root = tree.remove(tree.root, id);
      cout << "Programa removido com sucesso!" << endl;
    } break;
    case 3: {
      string id;
      cout << "Informe o ID do programa a ser buscado: ";
      cin >> id;
      auto start = std::chrono::high_resolution_clock::now();

      Node *result = tree.search(tree.root, id);
      auto end = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

      std::cout << "A busca levou " << duration.count() << " milissegundos.\n";

      if (result != nullptr) {
        cout << "Programa encontrado:" << endl;
        cout << "ID: " << result->data.id << endl;
        cout << "Title: " << result->data.title << endl;
        cout << "type: " << result->data.type << endl;
        cout << "description: " << result->data.description << endl;
        cout << "release_year: " << result->data.release_year << endl;
        cout << "age_certification: " << result->data.age_certification << endl;
        cout << "runtime: " << result->data.runtime << endl;
        cout << "genres: " << result->data.genres << endl;
        cout << "production_countries: " << result->data.production_countries
             << endl;
        cout << "seasons: " << result->data.seasons << endl;
        cout << "imdb_id: " << result->data.imdb_id << endl;
        cout << "imdb_score: " << result->data.imdb_score << endl;
        cout << "imdb_votes: " << result->data.imdb_votes << endl;
        cout << "tmdb_popularity: " << result->data.tmdb_popularity << endl;
        cout << "tmdb_score: " << result->data.tmdb_score << endl;
      } else {
        cout << "Programa nao encontrado." << endl;
      }
    } break;

    case 4: {
      int year;
      cout << "Informe o ano desejado: ";
      cin >> year;
      //--------------------------------------------------------

      //                vector<ProgramaNetFlix> allProgramas;
      //    tree.traverseTree(tree.getRoot(), allProgramas);
      //
      //    findTopRatedPrograms(allProgramas, year);

      //--------------------------------------------------------

      findTopRatedPrograms(tree, year);
    } break;
    case 5: {
      mostWatchedProgramByGenre(tree);
      break;
    }
    case 6: {
      analyzeDuration(tree);
      break;
    }
    case 7: {
      analyzeLaunchYear(tree);
      break;
    }
    case 8: {
      analyzeProductionCountry(tree);
      break;
    }
    case 9: {
      cout << "Encerrando o programa..." << endl;
      exit(0);
    }
    default:
      cout << "Opcao invalida. Tente novamente." << endl;
      break;
    }

    cout << endl;
  }

  return 0;
}
