#include "leitura.hpp"

void readPrincipal() {
    vector<string> filenames = {"dataset/Docs/filosofia.txt", "dataset/Docs/filosofia2.txt", "dataset/Docs/politica.txt", "dataset/Docs/ti2.txt", "dataset/Docs/ti.txt", "dataset/Docs/globalizacao.txt"};
    
    string line;
    string palavraLinha;
    bool decisao = false;
    int count = 0, contExpressoes = 0, NumStopWords = 0, Num_StopWords = 0;
    int cont = 0, linhai = 1, supremeCont = 0, tamanhoPalavra = 0;
    int aux = 0, contPalavras = 0;

    palavra_q word;
    palavra_q wordParagrados;

    unordered_map<string, palavra_q> mapPrintGeral; 
    unordered_map<string, bool>stopWords; 
    unordered_map<char, bool>pontos; 
    vector<string> palavras;
    preencheMapPontos(pontos); 
    ler_palavras(palavras);
    ofstream file_output ("dataset/output.data");
    file_output.close();
    
    bool mudou = false;

    readStopWords(stopWords);
    
    for (int j=0; j<palavras.size(); j++) {
        ofstream file_output("dataset/output.data", ios::app);
        string palavra = palavras[j];
        for (int i=0; i<filenames.size(); i++) {
            string filename = filenames[i];

            if(procurar_no_arquivo(filename, palavra) == true) {
                ifstream input_file(filename);
                

                if (!input_file.is_open()) {
                    cout << "Nao foi possivel abrir o arquivo" << filename << " " << endl;
                    return;
                }

                while (getline(input_file, line)) {
                    while (getline(input_file, line, '\n')) { 
                        cont++;
                        for (auto &c : line) {
                            c = tolower(c); 
                        }

                        line = converterAcentuadasParaMinusculas(line);
                        line = tiraReticencia(line);
                        istringstream ln(line);

                        if (line.size() > 1) {
                            decisao = false;

                            while (ln >> palavraLinha) { 
                                if (!temNumero(palavraLinha)) { 
                                    NumStopWords++;            
                                    supremeCont++;             
                                    if (Pontuacao(&palavraLinha, &contExpressoes, Num_StopWords)) {
                                        mudou = true; 
                                        NumStopWords = 0; 
                                        Num_StopWords = 0; 
                                    }

                                    palavraLinha = removePontuacao(palavraLinha, pontos); 
                                    
                                    auto it2 = stopWords.find(palavraLinha); 
                                    if (it2 == stopWords.end()) { 
                                        
                                        Num_StopWords++; 
                                        if (palavraLinha != "" && caractere_estranho(palavraLinha) && !palavra_igual(palavraLinha, palavras)) {

                                            inserePrintGeral(mapPrintGeral, palavraLinha, word, cont, supremeCont, contPalavras);

                                        }
                                    }
                                }
                            }

                            line.clear();
                        } else {
                            NumStopWords = 0;
                            Num_StopWords = 0;
                            decisao = true;
                            supremeCont = 0;  
                            linhai = cont + 1; 
                        }
                    }
                }
                if (!(decisao)) { 
                    contExpressoes = contExpressoes + 1;
                    contExpressoes = 0;
                    decisao = true;
                    linhai = cont + 1;
                    supremeCont = 0;
                }
                calcula_heap(mapPrintGeral, filename, palavras[j], file_output);
                mapPrintGeral.clear();
            }
            else {
                cout << endl << "------------- NÃO TEM A PALAVRA " << palavra << " NO ARQUIVO " << filename << " -------------" << endl;
            }
        }
    }
}



void  inserePrintGeral(unordered_map<string, palavra_q> &mapPrintGeral, string palavraLinha, palavra_q &wordParagrados, int cont, int supremeCont, int &contPalavras) {
    auto it = mapPrintGeral.find(palavraLinha); 

    if (it != mapPrintGeral.end()) {
        it->second.quantidade++; 
    } else {
        mapPrintGeral.insert({ palavraLinha, wordParagrados }); 
        contPalavras++;
    }
}

void readStopWords(unordered_map<string, bool> &stopWords) {
    string filename("dataset/stopwords.csv");
    ifstream input_file(filename, ios::in | ios::binary);
    string line;

    while (!input_file.eof()) {
        while (getline(input_file, line, '\n')) {
            if (line.size() >= 1) {
                for (auto &c : line) {
                    c = tolower(c);
                }

                stopWords.insert({ line,true });
            }
        }
    }
}

void preencheMapPontos(unordered_map<char, bool> &pontos) {
    pontos.insert({
        {'-', false},
        {'.', false},
        {',', false},
        {';', false},
        {'"', false},
        {'/', false},
        {'(', false},
        {')', false},
        {'[', false},
        {']', false},
        {'+', false},
        {'-', false},
        {'=', false},
        {'*', false},
        });
}

bool caractere_estranho(string s) {
    auto acentos = {"^" ,"--", " — ", " —", "—", "”", "-", "——", "“", "-”"};
    auto acentos_2 = {'"','-', '\xE2', '\x9D','\x80', '\x9C', '\x94'};

    for (auto a : acentos) {
        if (s.find(a) != s.npos) {
            return false;
        }
    }
    for (auto a : acentos_2) {
        if (s.find(a) != s.npos) {
            return false;
        }
    }

    return true;
}


bool isPonto(char c, unordered_map<char, bool>pontos) { 
    auto it = pontos.find(c);
    if (it != pontos.end()) return true;
    return false;
}

string removePontuacao(string num, unordered_map<char, bool>pontos) { 
   string palavraSemPonto;
   for (char c : num) {
        if (!isPonto(c, pontos)) {
            palavraSemPonto += c;
        }
    }
    return palavraSemPonto;
}

string tiraReticencia(string linha) {
    string retiBug = ". . .";
    size_t pos = linha.find(retiBug);
    if (pos != std::string::npos)
        linha.erase(pos, retiBug.length());

    string reti = "...";
    size_t pos2 = linha.find(reti);
    if (pos2 != std::string::npos)
        linha.erase(pos2, reti.length());

    string reti2 = "..";
    size_t pos3 = linha.find(reti2);
    if (pos3 != std::string::npos)
        linha.erase(pos3, reti2.length());

    return linha;
}


bool temNumero(string palavra) {
    for (int i = 0;i < palavra.size();i++) {
        if (isdigit(palavra[i])) return true;
    }

    return false;
}


bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWords) { 
    bool encontrar = false;

    char ponto = '.', exclamacao = '!', interrogacao = '?';

    size_t pos1 = (*num).find(ponto);
    if (pos1 != std::string::npos) {  
        if (!ispunct((*num)[pos1 - 1])) {
            *contExpressoes = *contExpressoes + 1;
            (*num).erase(pos1, 1);
            encontrar = true;
        }
    }
    size_t pos2 = (*num).find(exclamacao);
    if (pos2 != std::string::npos) {  
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos2, 1);
        encontrar = true;
    }
    size_t pos3 = (*num).find(interrogacao);
    if (pos3 != std::string::npos) {  
        *contExpressoes = *contExpressoes + 1;
        (*num).erase(pos3, 1);
        encontrar = true;
    }

    return encontrar;
}

void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line) {

    for (auto itE = map.begin();itE != map.end();++itE) {
        auto itS = line.find(itE->first);
        if (itS != string::npos) {
            itE->second.push_back(cont);
        }
    }
}

string converterAcentuadasParaMinusculas(string num) {
    string maiuscula = "ÁÀÃÉÈÍÌÓÒÚÙÕÂÊÎÔÛ";
    string minuscula = "áàãéèíìóòúùõâêîôû";

    for (size_t i = 0; i < maiuscula.size(); i++) {
        replace(num.begin(), num.end(), maiuscula[i], minuscula[i]);
    }
    return num;
}

void calcula_heap(unordered_map<string, palavra_q> &mapPrintGeral, string nome_arquivo, string nome_palavra, ofstream& file_output) {
    vector<pair<string, int>> min_heap;
    bool verdade = false;
    int cont = 0;

    for (auto& x : mapPrintGeral) {
        if (min_heap.size() < K) {
            min_heap.push_back({x.first, x.second.quantidade});
            faz_a_heap(min_heap);
            cont ++;
        }
        else {
            if (x.second.quantidade > min_heap[0].second) {
                min_heap[0].second = x.second.quantidade;
                min_heap[0].first = x.first;
                faz_a_heap(min_heap);
            }
        }
    }
    imprimir(min_heap, nome_arquivo, nome_palavra, file_output);
    arvore_binaria(min_heap, file_output);
    AVL(min_heap, file_output);
    huffman(min_heap, file_output);

    min_heap.clear();
}


void faz_a_heap(vector<pair<string, int>> &min_heap) {
   int size = min_heap.size();

    for (int i = (size / 2) - 1; i >= 0; --i) {
        int menor = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && min_heap[left].second < min_heap[menor].second) {
            menor = left;
        }

        if (right < size && min_heap[right].second < min_heap[menor].second) {
            menor = right;
        }

        if (menor != i) {
            swap(min_heap[i].second, min_heap[menor].second);
            swap(min_heap[i].first, min_heap[menor].first);
        }
    }
}

void imprimir(vector<pair<string, int>> &min_heap, string nome_arquivo, string nome_palavra, ofstream& file_output) {
    int size = min_heap.size();
    cout << "PALAVRA: " << nome_palavra << endl;
    cout << "ARQUIVO " << nome_arquivo << endl;


    file_output << endl << "===================================================================" << endl;
    file_output << "PALAVRA: " << nome_palavra << endl;
    file_output << "ARQUIVO " << nome_arquivo << endl;
    file_output << "EXIBIÇÃO InOrder -> " << endl << endl;
}

void ler_palavras(vector<string> &palavras) {
    ifstream arquivo_leitura("dataset/input.data");
    int i=1;
    char caractere;

    if (!arquivo_leitura.is_open()) {
        cout << endl << "Erro ao abrir o arquivo" << endl;
        return;
    }

    string linha;

    while (arquivo_leitura >> linha) {
        cout << "Palavra " << i << ":" << linha << endl;
        palavras.push_back(linha);
        i++;
    }
}

bool procurar_no_arquivo(string arquivo, string palavra) {
    ifstream arquivos(arquivo);

    if (!arquivos.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return false;
    }

    string palavra_texto;

    while (arquivos >> palavra_texto) {
        if (palavra_texto == palavra) {
            return true;
        }
    }
    
    
    return false;
}

bool palavra_igual(string palavra, vector<string> &palavras) {
    for (int i=0; i<palavras.size(); i++) {
        if (palavra == palavras[i]) {
            return true;
        }
    }
    return false;
}

//================================= ÁRVORE AVL =================================

void AVL(vector<pair<string, int>> &min_heap, ofstream& file_output) {
    AVLNode* raiz = nullptr;

    for (const auto& item : min_heap) {
        raiz = insertAVL(raiz, item.second, item.first);
    }
    file_output << endl << "AVL TREE -> " << endl;
    printInOrder(raiz, file_output);

    destroyAVL(raiz);
}

void destroyAVL(AVLNode* node) {
    if (node == nullptr) return;

    destroyAVL(node->left);
    destroyAVL(node->right);
    
    delete node;

    node = nullptr;
}

int getHeight(AVLNode* node) {
    if (node == nullptr) 
        return 0;
    return node->height;
}

void updateHeight(AVLNode* node) {
    if (node != nullptr) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

int getBalanceFactor(AVLNode* node) {
    if (node == nullptr) 
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}


AVLNode* rotateLeft(AVLNode* y) {
    AVLNode* x = y->right;
    AVLNode* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) +1;
    x->height = max(getHeight(x->left), getHeight(x->right)) +1;

    return x;
}

AVLNode* rotateRight(AVLNode* x) {
    AVLNode* y = x->left;
    AVLNode* T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) +1;
    y->height = max(getHeight(y->left), getHeight(y->right)) +1;

    return y;
}


AVLNode* insertAVL(AVLNode* node, int quantidade, const string& palavra) {
    if (node == nullptr) {
        return new AVLNode(quantidade, palavra);
    }

    if (quantidade < node->quantidade) {
        node->left = insertAVL(node->left, quantidade, palavra);
    } else if (quantidade > node->quantidade) {
        node->right = insertAVL(node->right, quantidade, palavra);
    } else {
        node->vetor_palavras.push_back(palavra);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
   
    int balance = getBalanceFactor(node);

    if (balance > 1) {
        if (quantidade < node->left->quantidade) {
            return rotateRight(node);
        } else {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
    }

    if (balance < -1) {
        if (quantidade > node->right->quantidade) {
            return rotateLeft(node);
        } else {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
    }
    return node;
}



void printInOrder(AVLNode* node, ofstream& file_output) {
    if (node == nullptr) return;
    printInOrder(node->left, file_output);
    file_output << node->quantidade << ": " << node->palavra << endl;
    for(auto x: node->vetor_palavras) {
        file_output << node->quantidade << ": " << x << endl;
    }
    printInOrder(node->right, file_output);
}

//============================ ÁRVORE BINÁRIA ============================

BinaryNode* insertBinaria(BinaryNode* node, int quantidade, const string& palavra) {
    if (node == nullptr) {
        return new BinaryNode(quantidade, palavra);
    }

    if (quantidade < node->quantidade) {
        node->left = insertBinaria(node->left, quantidade, palavra);
    } else if (quantidade > node->quantidade) {
        node->right = insertBinaria(node->right, quantidade, palavra);
    } else {
        node->right = insertBinaria(node->right, quantidade, palavra);
    }

    updateBinaryHeight(node);

    return node;
}

void arvore_binaria(vector<pair<string, int>> &min_heap, ofstream& file_output) {
    BinaryNode* raiz = nullptr;

    for (const auto& item : min_heap) {
        raiz = insertBinaria(raiz, item.second, item.first);
    }
    file_output << "BINARY TREE -> " << endl;
    printInOrderBinary(raiz, file_output);

    destroyBinary(raiz);
}

void destroyBinary(BinaryNode* node) {
    if (node == nullptr) return;

    destroyBinary(node->left);
    destroyBinary(node->right);
    
    delete node; 
    node = nullptr;
}

void updateBinaryHeight(BinaryNode* node) {
    if (node != nullptr) {
        node->height = max(getBinaryHeight(node->left), getBinaryHeight(node->right)) + 1;
    }
}

int getBinaryHeight(BinaryNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

void printInOrderBinary(BinaryNode* node, ofstream& file_output) {
    if (node == nullptr) return;
    printInOrderBinary(node->left, file_output);
    file_output << node->quantidade << ": " << node->palavra << endl;
    printInOrderBinary(node->right, file_output);
}

// =================== HUFFMAN =====================

HuffmanNode* buildHuffmanTree(vector<pair<string, int>>& min_heap) {
    priority_queue<pair<int, HuffmanNode*>, vector<pair<int, HuffmanNode*>>, greater<pair<int, HuffmanNode*>>> pq;

    for (auto& pair : min_heap) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        pq.push({pair.second, node});
    }

    while (pq.size() > 1) {
        pair<int, HuffmanNode*> leftNode = pq.top();
        pq.pop();
        pair<int, HuffmanNode*> rightNode = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode("", leftNode.first + rightNode.first);
        newNode->left = leftNode.second;
        newNode->right = rightNode.second;

        pq.push({newNode->frequency, newNode});
    }

    return pq.top().second;
}

void printHuffmanTreeBFS(HuffmanNode* root, ofstream& file_output) {
    string code="";
    if (!root)
        return;

    queue<pair<HuffmanNode*, string>> q;
    q.push({root, code});

    while (!q.empty()) {
        pair<HuffmanNode*, string> currentPair = q.front();
        q.pop();

        HuffmanNode* current = currentPair.first;
        string currentCode = currentPair.second;

        if (current->left == nullptr && current->right == nullptr) {
            file_output << current->data << ": " << currentCode << endl;
        }

        if (current->left)
            q.push({current->left, currentCode + "0"});

        if (current->right)
            q.push({current->right, currentCode + "1"});
    }
}

void huffman(vector<pair<string, int>> &min_heap, ofstream& file_output) {
    HuffmanNode* raiz = buildHuffmanTree(min_heap);

    file_output << endl << "HUFFMAN CODE ->" << endl;

    printHuffmanTreeBFS(raiz, file_output);

}