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

Para explicações detalhadas sobre funcionamento da HASH e da heap presentes no código, acesse o link: [WordRecurrence](https://github.com/Parreirass/WordRecurrence)

## Testes Realizados

## Conclusão

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
