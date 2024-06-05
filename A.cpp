#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <stack>
#include <string>
#include <windows.h> // Inclua esta biblioteca para usar SetConsoleOutputCP
using namespace std;

// Variáveis globais para armazenar os tempos de execução
long long tempoBubbleSort = 0;
long long tempoQuickSort = 0;
long long tempoSelectionSort = 0;

// Função para limpar a tela
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função para configurar a codificação do console para UTF-8
void setUTF8Console() {
    #ifdef _WIN32
        SetConsoleOutputCP(65001); // Defina a codificação do console para UTF-8
    #endif
}

// Função para ler dados de um arquivo para um vetor
vector<int> readDataFromFile(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    int value;

    while (file >> value) {
        data.push_back(value);
    }

    return data;
}

// Função para ordenar um vetor usando Bubble Sort
void bubbleSort(int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    tempoBubbleSort = chrono::duration_cast<chrono::microseconds>(end - start).count();
}


// Função para particionar o vetor no Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Função para ordenar um vetor usando Quick Sort
void quickSort(int arr[], int low, int high) {
    auto start = chrono::high_resolution_clock::now();
    
    stack<pair<int, int>> st;
    st.push(make_pair(low, high));

    while (!st.empty()) {
        low = st.top().first;
        high = st.top().second;
        st.pop();

        int pi = partition(arr, low, high);

        if (pi - 1 > low) {
            st.push(make_pair(low, pi - 1));
        }
        if (pi + 1 < high) {
            st.push(make_pair(pi + 1, high));
        }
    }

    auto end = chrono::high_resolution_clock::now();
    tempoQuickSort = chrono::duration_cast<chrono::microseconds>(end - start).count();
}


// Função para ordenar um vetor usando Selection Sort
void selectionSort(int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }

    auto end = chrono::high_resolution_clock::now();
    tempoSelectionSort = chrono::duration_cast<chrono::microseconds>(end - start).count();
}


// Função para imprimir o vetor
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n" << endl;
}

// Função para exibir o menu e obter a escolha do usuário
int displayMenu() {
    cout << R"(

 /$$      /$$                                 /$$                              
| $$$    /$$$                                | $$                              
| $$$$  /$$$$  /$$$$$$   /$$$$$$   /$$$$$$$ /$$$$$$    /$$$$$$   /$$$$$$       
| $$ $$/$$ $$ |____  $$ /$$__  $$ /$$_____/|_  $$_/   /$$__  $$ /$$__  $$      
| $$  $$$| $$  /$$$$$$$| $$$$$$$$|  $$$$$$   | $$    | $$  \__/| $$  \ $$      
| $$\  $ | $$ /$$__  $$| $$_____/ \____  $$  | $$ /$$| $$      | $$  | $$      
| $$ \/  | $$|  $$$$$$$|  $$$$$$$ /$$$$$$$/  |  $$$$/| $$      |  $$$$$$/      
|__/     |__/ \_______/ \_______/|_______/    \___/  |__/       \______/       
                                                                                                                                                                                                                           
                                                                                                    
    1. Escolher um arquivo .txt
    2. Sair
)";
    int choice;
    cout << "Escolha uma opção: ";
    cin >> choice;

    // Verificar se a entrada é válida
    if (cin.fail()) {
        cin.clear(); // Limpar a flag de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada inválida
        choice = -1; // Definir escolha como inválida
        clearScreen();
    }

    return choice;
}

// Função para exibir o menu após a ordenação e obter a escolha do usuário
int displayPostSortMenu() {

    // ExibE os tempos de execução
    cout << "Tempo de execução do Bubble Sort: " << tempoBubbleSort << " microssegundos" << endl;
    cout << "Tempo de execução do Quick Sort: " << tempoQuickSort << " microssegundos" << endl;
    cout << "Tempo de execução do Selection Sort: " << tempoSelectionSort << " microssegundos" << endl;

    cout << R"(
    1. Mostrar o array ordenado
    2. Voltar ao menu
)";
    int choice;
    cout << "Escolha uma opção: ";
    cin >> choice;

    // Verificar se a entrada é válida
    if (cin.fail()) {
        cin.clear(); // Limpar a flag de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada inválida
        choice = -1; // Definir escolha como inválida
        clearScreen();
    }

    return choice;
}

// Função para selecionar o método de ordenação a ser exibido
int chooseSortMethod() {
    cout << R"(
    1. Bubble Sort
    2. Quick Sort
    3. Selection Sort
)";
    int choice;
    cout << "Escolha uma opção: ";
    cin >> choice;

    // Verificar se a entrada é válida
    if (cin.fail()) {
        cin.clear(); // Limpar a flag de erro
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada inválida
        choice = -1; // Definir escolha como inválida
        clearScreen();
    }

    return choice;
}

int main() {
    setUTF8Console(); // Configurar a codificação do console para UTF-8

    vector<int> data;
    vector<int> arr1, arr2, arr3;
    int N = 0;
    while (true) {
        int choice = displayMenu();
        if (choice == 2) {
            cout << "Saindo do programa..." << endl;
            break;
        } else if (choice == 1) {
            string filename;
            cout << "Digite o nome do arquivo .txt: ";
            cin >> filename;
            
            // Verificar se a entrada é válida
            if (cin.fail()) {
                cin.clear(); // Limpar a flag de erro
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descartar entrada inválida
                cout << "Entrada inválida. Por favor, insira um nome de arquivo válido." << endl;
                continue; // Volte para o início do loop
            }
            
            // Verificar e adicionar a extensão .txt se necessário
            if (filename.size() <= 4 || filename.substr(filename.size() - 4) != ".txt") {
                filename += ".txt";
            }
            
            clearScreen(); // Limpar a tela após digitar o nome do arquivo
            
            data = readDataFromFile(filename);
            N = data.size();

            // Verificação se os dados foram carregados corretamente
            if (N == 0) {
                cerr << "Erro: Não foi possível carregar os dados ou o arquivo está vazio." << endl;
                continue;
            }

            // Cópia dos dados para diferentes vetores
            arr1 = data;
            arr2 = data;
            arr3 = data;

            
            bubbleSort(arr1.data(), N);
            quickSort(arr2.data(), 0, N-1);
            selectionSort(arr3.data(), N);

            while (true) { // Loop para perguntar novamente após exibir o array ordenado
                // Menu após a ordenação
                int postSortChoice = displayPostSortMenu();
                if (postSortChoice == 2) {
                    clearScreen();
                    break;
                } else if (postSortChoice == 1) {
                    int sortMethodChoice = chooseSortMethod();
                    if (sortMethodChoice == 1) {
                        cout << "Array ordenado por Bubble Sort: ";
                        printArray(arr1.data(), N);
                    } else if (sortMethodChoice == 2) {
                        cout << "Array ordenado por Quick Sort: ";
                        printArray(arr2.data(), N);
                    } else if (sortMethodChoice == 3) {
                        cout << "Array ordenado por Selection Sort: ";
                        printArray(arr3.data(), N);
                    }
                } else {
                    cout << "Opção inválida, tente novamente." << endl;
                }
            }
        } else {
            cout << "Opção inválida, tente novamente." << endl;
        }
    }

    return 0;
}
