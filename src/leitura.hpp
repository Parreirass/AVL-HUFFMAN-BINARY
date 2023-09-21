#ifndef LEITURA_HPP
#define LEITURA_HPP

#include <bits/stdc++.h>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <locale>
#include <fstream>
#include <vector>

#define endl '\n'
#define K 10

using namespace std;

typedef struct palavra {
    int quantidade = 1;
}palavra_q;

struct AVLNode {
    int quantidade;
    string palavra;
    int height;
    AVLNode* left;
    AVLNode* right;
    vector<string> vetor_palavras;

    AVLNode(int d, const string& l) : quantidade(d), palavra(l), height(1), left(nullptr), right(nullptr) {}
};

struct BinaryNode {
    int quantidade;
    string palavra;
    int height;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(int d, const string& l) : quantidade(d), palavra(l), height(1), left(nullptr), right(nullptr) {}
};

struct HuffmanNode {
    string data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(string data, int frequency) {
        this->data = data;
        this->frequency = frequency;
        left = right = nullptr;
    }
};

void readPrincipal();

void preencheMapPontos(unordered_map<char, bool> &pontos);
void readStopWords(unordered_map<string, bool> &stopWords);

void inserePrintGeral(unordered_map<string, palavra_q> &mapPrintGeral, string palavraLinha, palavra_q &wordParagrados, int cont, int supremeConte, int &contPalavras);

void checaExpressao(unordered_map<string, vector<int>> &map, int cont, string line);
string tiraReticencia(string linha);
string removePontuacao(string num, unordered_map<char, bool>pontos);
string converterAcentuadasParaMinusculas(string num);
bool temNumero(string palavra);
bool Pontuacao(string *num, int *contExpressoes, int &Num_StopWord);
bool isPonto(char c, unordered_map<char, bool>pontos);

void calcula_heap(unordered_map<string, palavra_q> &mapPrintGeral, string nome_arquivo, string nome_palavra, ofstream& file);
void faz_a_heap(vector<pair<string, int>> &min_heap);
void imprimir(vector<pair<string, int>> &min_heap, string nome_arquivo, string nome_palavra, ofstream& file_output);

void ler_palavras(vector<string> &palavras);
bool procurar_no_arquivo(string arquivo, string palavra);

bool caractere_estranho(string s);
bool palavra_igual(string palavra, vector<string> &palavras);

void arvore_binaria(vector<pair<string, int>> &min_heap, ofstream& file_output);
void huffman(vector<pair<string, int>> &min_heap, ofstream& file_output);
void AVL(vector<pair<string, int>> &min_heap, ofstream& file_output);

BinaryNode* insertBinaria(BinaryNode* node, int quantidade, const string& palavra);
void destroyBinary(BinaryNode* node);
void updateBinaryHeight(BinaryNode* node);
int getBinaryHeight(BinaryNode* node);
void printInOrderBinary(BinaryNode* node, ofstream& file_output);

void printInOrder(AVLNode* node, ofstream& file_output);
AVLNode* insertAVL(AVLNode* node, int quantidade, const string& palavra);
AVLNode* rotateRight(AVLNode* y);
AVLNode* rotateLeft(AVLNode* x);
void updateHeight(AVLNode* node);
int getHeight(AVLNode* node);
int getBalanceFactor(AVLNode* node);
void destroyAVL(AVLNode* node);

HuffmanNode* buildHuffmanTree(vector<pair<string, int>>& min_heap);
void printHuffmanTreeBFS(HuffmanNode* root, ofstream& file_output);

#endif