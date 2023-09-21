# AVL-HUFFMAN-BINARY
AEDS II | CEFET-MG

<div style="display: inline-block;">    
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> 
<img align="center" height="20px" width="80px" src="https://img.shields.io/badge/Made%20for-VSCode-1f425f.svg"/> 
</a> 
</div>

<p> </p>
<p> </p>

## Proposta do Projeto

A proposta geral do projeto é criar um sistema que oferece sujestões de palavras relacionadas à partir de uma palavra lida. 
Existe um arquivo com palavras que serão lidas e, caso a palavra trabalhada exista em algum dos arquivos de texto selecionados, é construída uma árvore de cada tipo com as `K` palavras mais recorrentes, com o objetivo de exibir uma sujestão de próxima palavra relacionada.
> São utilizadas árvores AVL, binária e "Código de huffman", que aperfeiçoa a árvore binária.
- É necessário usar uma estrutura `HASH` para o armazenamento das palavras.
  - São consideradas palavras apenas aquelas que possuem todos os caracteres presentes na tabela `ASCII`.
  - Sinais de pontuação são removidos antes da análise de palavras.
- As `N` palavras mais recorrentes são selecionadas utilizando uma estrutura `HEAP`.
- Existe um arquivo chamado `stopwords.csv` que contém palavras consideradas como *stopwords*, elas não devem ser consideradas como palavras à serem analisadas as recorrências. Caso fossem consideradas como palavras comuns, elas iriam ser as que mais apareceriam nos textos.
- Para cada texto em que a palavra trabalhada aparece, é exibido uma árvore de cada tipo no arquivo `output.txt` com as `N` palavras mais recorrentes no texto.

|          Sinais de pontuação  | Stop words                                      |
|-------------------------------|-------------------------------------------------|
| `.`,   `!`,   `?`                   |   `artigos(a, o, as,os), conjunções(e, ou), palavras comuns (aquela, estiver) `  |

## Arquivos e Funções

O projeto é dividido entre três arquivos de códigos própriamente ditos: `leitura.hpp`, `leitura.cpp` e `main.cpp`.
Arquivos de texto auxiliares são utilizados para leitura e escrita.

|  Arquivo                        |   Função                                                                                          |
| ------------------------------- | ------------------------------------------------------------------------------------------------- |
|  `main.cpp`                       | Arquivo principal para iniciar e chamar as funções do código                                                    |
|  `leitura.hpp`                  | Define as funções e as estruturas que foram utilizadas no código |
|  `leitura.cpp`                  | Contém o escopo de todas as funções que foram utilizadas |
| `stopwords.csv` | arquivo que contem as stop words|
| `arquivo_de_leitura.txt` | um dos arquivos de entrada principal no qual será feita toda a análise |
| `input.txt` | arquivo de entrada com as palavras a serem lidas |
| `output.txt` | arquivo de escrita com a exibição das árvores |

> O arquivo `main.cpp` "chama" apenas uma função definida no `leitura.hpp` e processada no `leitura.cpp`, chamada `readPrincipal()`. Ela, por sua vez, organiza todo o processo e as demais funções presentes no projeto. 

## Lógica Implementada

A função `readPrincipal()` trabalha todo o código e invoca as demais funções. 
- Existem duas variáveis do tipo `vector` que "coordenam" qual palavra está sendo trabalhada por qual arquivo:
  - *filenames*: Armazena os arquivos de texto a serem trabalhados
  - *palavras*: Armazena as palavras (`input.txt`) a serem trabalhadas. É preenchido na função `ler_palavras()`.

A função `procurar_no_arquivo()` recebe a palavra trabalhada e o arquivo de texto que será trabalhado, caso ela exista nesse arquivo, é feita a tabela `HASH` separando cada palavra e sua respectiva quantidade de aparições para, posteriormente, ser feita a `heap`, que, por sua vez, separará as *K* palavras mais presentes.

O projeto *WordRecurrence* (repositório) usa a mesma estrutura de alocamento de palavras e suas respectivas quantidades e criação da heap com as palavras mais frequentes que esse repositório.
Para explicações detalhadas sobre funcionamento da HASH e da heap presentes no código, acesse o link: [WordRecurrence](https://github.com/Parreirass/WordRecurrence)

Com a HASH feita e a heap construída, podemos passar para a construção das árvores.
> Cada árvore é feita a partir de um vector (*heap*) de *pair*, em que cada posição armazena a palavra e sua respectiva quantidade de aparições no texto. A inserção e balanceamento são feitos em relação à quantidade de palavras.

A função `calcula_heap()` já faz tanto o processo de criação da heap quanto o de criação de todas as árvores. 

#### Ávore Binária
- Existe uma função chamada `arvore_binária()`, que cria uma variável de ponteiro do tipo *BinaryNode* apontando para nulo. Depois, percorre posição por posição do vector *min_heap* e vai fazendo a inserção direcionando cada ponteiro para cada filho esquerdo ou direito da posição da árvore da seguinte forma:
  - Caso o próximo valor seja menor, é inserido como filho esquerdo.
  - Caso o próximo valor seja maior, é inserido como filho direito.
  - Caso o próximo valor seja igual, é inserido como filho direito.
``` C++ code
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
```
- Ao fim da inserção, a função `printInOrderBinary()` imprime a árvore no formato *InOrder* no arquivo `output.txt`.
Finalmente, a função `destroyBinary()` libera a memória alocada para a construção da árvore.
<center>
  <img src = "img/image11.gif">
</center>

#### Código de Huffman
A construção de uma árvore de Huffman está diretamente relacionada à construção de uma árvore binária, sendo uma espécie de otimização da mesma, utilizando a concatenação de números `0` e `1`, dependendo da presença de filho esquerdo ou direito.
- Inicialmente, a função `buildHuffmanTree()` cria uma fila de prioridade que encontra os dois *"nós"* menos frequentes mais rapidamente. Para toda posição da `min_heap` é criado um nó *HuffmanNode*
- A cada iteração, os dois nós com as menores frequências são retirados da fila de prioridade.
- Um novo nó é criado como pai desses dois nós, com uma frequência igual à soma das frequências dos filhos.
- O novo nó é inserido de volta na fila de prioridade.
- O processo continua até que haja apenas um nó na fila de prioridade, que se torna a raiz da árvore de Huffman.

```C++ Code
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
```

> Uma vez que a árvore de Huffman está completa, códigos binários são atribuídos aos símbolos com base na estrutura da árvore. Os caminhos da raiz da árvore até os nós folha determinam os códigos. Aos ramos da esquerda são concatenados o código binário 0, e os ramos da direita são concatenados o código binário 1.

- Como os códigos de Huffman são atribuídos com base na frequência dos símbolos, símbolos mais comuns terão códigos mais curtos e símbolos menos comuns terão códigos mais longos. Isso resulta em uma redução geral no tamanho dos dados, uma vez que os símbolos mais comuns são representados de forma mais eficiente com menos bits.

> Por exemplo, considere um texto que contenha principalmente as palavras "mundo", "planeta", "terra" e "espaço", com a palavra "planeta" sendo a mais comum. Na árvore de Huffman, "planeta" provavelmente terá um código curto, como "10", enquanto as outras palavras terão códigos mais longos, como "110", "111", etc. Quando você compacta o texto usando esses códigos, ele se torna mais curto do que se você usasse a representação completa de cada letra.

<center>
  <img src = "img/huffman.gif">
  <img src = "img/huffman2.jpg">
</center>

#### Árvore AVL
Existe uma função chamada `insertAVL()` que inicializa o novo nó da árvore AVL. A cada inserção é verificado o valor *quantidade* armazenado em cada nó já presente na árvore, para ver em qual posição o novo nó seria inserido:
- Caso o novo nó seja maior (chave) que o atual, ele será inserido à direita.
- Caso o novo nó seja menor (chave) que o atual, ele será inserido à esquerda.
- Caso o novo nó seja igual (chave) ao atual, a palavra será adicionada à um vector de palavras repetidas e irá apontar para o nó já presente.
A árvore AVL possui um diferencial em relação à *ÁRVORE BINÁRIA*, o **balanceamento**. O balanceamento serve para equilibrar a árvore em relação aos filhos direito e esquerdo de cada nó, afim de que um lado não se torne significativamente maior que outro.

```C++ Code
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
```

Existem 4 tipos de rotação:
- **Rotação simples à direita**
  - Na rotação simples à direita, cada nó se move uma posição para a direita da posição atual.
  - Quando um nó tem um fator de equilíbrio de -2 e seu filho à direita tem um fator de equilíbrio de -1 ou 0, uma rotação simples à direita é aplicada para restaurar o equilíbrio.
- **Rotação simples à esquerda**
  - Na rotação simples à esquerda, cada nó se move uma posição para a esquerda da posição atual.
  - Quando um nó tem um fator de equilíbrio de 2 e seu filho à esquerda tem um fator de equilíbrio de 1 ou 0, uma rotação simples à esquerda é aplicada para restaurar o equilíbrio.
- **Rotação dupla à direita**
  - As rotações duplas à direita são uma combinação de uma única rotação para a esquerda seguida de uma rotação para a direita.
  - Quando um nó tem um fator de equilíbrio de -2 e seu filho à direita tem um fator de equilíbrio de 1, uma rotação dupla à direita-esquerda é aplicada.
  - Primeiro, cada nó se move uma posição para a esquerda. Depois, se move uma posição para a direita da posição atual.

- **Rotação dupla à esquerda**
  - As rotações duplas à esquerda são uma combinação de uma única rotação para a direita seguida de uma rotação para a esquerda.
  - Quando um nó tem um fator de equilíbrio de 2 e seu filho à esquerda tem um fator de equilíbrio de -1, uma rotação dupla à esquerda-direita é aplicada.
  - Primeiro, cada nó se move uma posição para a direita. Depois, se move uma posição para a esquerda da posição atual.

> Um filho à esquerda equivale à um fator de equilíbrio *-1* e um à direita equivale à um fator de equilíbrio *+1*.

A escolha da rotação depende do tipo de desequilíbrio e da posição do nó desequilibrado em relação ao nó pai e ao avô. O objetivo das rotações é restaurar o equilíbrio da árvore AVL para garantir que a diferença de altura entre as subárvores esquerda e direita em todos os nós seja mantida em -1, 0 ou 1. Isso garante um tempo de busca eficiente em árvores AVL.

<center>
  <img src = "img/avl.gif">
</center>

## Testes Realizados
- Os testes que serão apresentados abaixo foram feitos em um Notebook Acer Nitro 5 (intel i5 10300H - gtx 1650 - 8gb ram).
> A exibição das árvores está no modelo "In Order" (crescente).
> Foi definido o *K=10* através de um *#define K 10*, logo cada árvore terá 10 elementos.

<img src ="img/palavras.jpeg">

- Palavras contidas no arquivo `input.txt` que serão lidas e trabalhadas no código. Caso a palavra analisada esteja em um arquivo de texto, serão feitas as árvores com as *K* palavras mais recorrentes daquele texto.

<br><br>

<img src = "img/terminal.jpeg">

- O terminal exibe qual palavra está sendo trabalhada e em qual arquivo essa palavra está sendo buscada. Caso ela esteja presente, as árvores serão escritas no arquivo `output.txt`, caso o contrário, é exibida uma mensagem no terminal informando a sua ausência no texto.

<br><br>

<img src = "img/output.jpeg">

- Esse é um exemplo das árvores criadas a partir da palavra *teoria* no arquivo de texto `filosofia.txt`. As árvores estão exibidas no modelo "In Order" e, as árvores Binária e AVL exibem a palavra e sua respectiva recorrência, já a Huffman, exibe a palavra seguida de seu respectivo código.

> Ao final da execução, é exibido no terminal o tempo gasto para toda a execução do código.

## Conclusão
O projeto *AVL-HUFFMAN-BINARY* cumpre seu papel com êxito. Com proposta de busca em um arquivo de texto e criação de árvores de recorrência, o programa desempenha papel satisfatório e correto na construção e exibição das árvores binária, avl e huffman.
É possível observar as diferenças entre as árvores e em qual momento é mais vantajoso a utilização de qual árvore. 
- A árvore binária apresenta uma estrutura simplória de inserção e remoção. Porém a ineficiência para busca é seu ponto negativo.
- A árvore AVL tem o balanceamento como seu benefício, mantendo a complexidade de inserção e remoção em O(logn). Entretanto, o prório balanceamento a deixa sua construção um tanto quanto complexa.
- A árvore Huffman tem a compactação de dados como seu ponto positivo, tornando eficaz na redução do espaço de armazenamento. Já como ponto negativo, a ineficiência para busca pode ser citada.

**Portanto, a escolha entre essas estruturas de árvore depende da aplicação específica e das necessidades de desempenho e espaço.**


## Compilação e Execução
Esse exemplo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:

| Comando                |  Função                                                                                           |
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o gcc, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

<p> </p>

#### Felipe Parreiras
<div style="display: inline-block;">
<a href="https://t.me/fparreiras">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
</a>

<a href="https://www.linkedin.com/in/felipe-parreiras-56b075277/">
<img align="center" height="20px" width="90px" src="https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white"/>
</a>
