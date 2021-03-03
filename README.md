# Projeto
Este projeto consiste na implementação do Algoritmo de Bron-Kerbosch, em duas versões: com pivotamento e sem pivotamento, além de outras funcionalidades necessárias para a manipulação e implementação de um **grafo**. Além do cálculo do Coeficiente de Aglomeração do grafo.

Haviam duas possibilidades de escolha de linguagem, C e C++. A escolhida foi **Linguagem C**.

## Algoritmo de Bron-Kerbosch

Na ciência da computação, o algoritmo de Bron – Kerbosch é um algoritmo de enumeração para encontrar todos os **cliques máximos** em um grafo não direcionado. Ou seja, ele lista todos os subconjuntos de vértices com as duas propriedades de que cada par de vértices em um dos subconjuntos listados é conectado por uma aresta e nenhum subconjunto listado pode ter quaisquer vértices adicionais adicionados a ele, preservando sua conectividade completa. O algoritmo Bron – Kerbosch foi projetado pelos cientistas holandeses Coenraad Bron e Joep Kerbosch, que publicou sua descrição em 1973. [(Wikipédia)](https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm)

### Sem pivotamento x com pivotamento
A forma básica do algoritmo, descrita acima, é ineficiente no caso de grafos com muitos cliques não máximos: ele faz uma chamada recursiva para cada clique, máximo ou não. Para economizar tempo e permitir que o algoritmo retroceda mais rapidamente nos ramos da pesquisa que não contêm cliques máximos, Bron e Kerbosch introduziram uma variante do algoritmo envolvendo um "vértice pivô" u , escolhido de P (ou mais geralmente, como investigadores posteriores realizado, a partir de P  ⋃  X ). Qualquer clique máximo deve incluir u ou um de seus não vizinhos, caso contrário, o clique poderia ser aumentado adicionando u a ele. Portanto, apenas u e seus não vizinhos precisam ser testados como escolhas para o vértice v que é adicionado a R em cada chamada recursiva ao algoritmo. [(Wikipédia)](https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm)

## Grafo

O grafo utilizado para teste foi de uma base de dados **The Network Data Repository with Interactive Graph Analytics and Visualization** o qual possui informações da cadeia de socialização de uma população de 62 golfinhos em uma comunidade vivendo Doubtful Sound, Nova Zelândia.

**OBS**: Mais informações contidas no arquivo soc-dolphins.mtx

Para a inserção dos vértices no grafo, o arquivo soc-dolphins.mtx provém uma lista de pares dos vértices que possuem arestas entre si o qual pode ser fácilmente representado por uma **Lista de Adjacência**.

## Implementação

A abstração do grafo foi convertida para uma estrutura o qual possui o número total de vértices e um array de Nodes, sendo Node uma outra estrutura definida para atuar como uma lista tradicional de Estrutura de Dados. 

Para a estrutura Grafo, há um inteiro que armazena o número total de vértices e um ponteiro de ponteiro para armazenar o endereço inicial do array.

```
typedef struct Graph{
    int numVertices;
    struct Node **adjLists;
} Graph;
```
Para a estrutura Node, há um inteiro que armazena o número correspondente ao vértice e um ponteiro que apontará para o próximo endereço da lista.

```
typedef struct Node{
    int vertex;
    struct Node *next;
} Node;
```

## Coeficiente de Agloremação

Na teoria dos grafos, o coeficiente de agrupamento (clustering coefficient) mede o grau com que os nós de um grafo tendem a agrupar-se. Existem duas versões desta métrica: coeficiente de agrupamento global e coeficiente de agrupamento local. O coeficiente de agrupamento global foi concebido para fornecer uma visão geral do agrupamento na rede, já o coeficiente de agrupamento local fornece uma indicação da inserção dos nós individuais. [(Wikipédia)](https://pt.wikipedia.org/wiki/Coeficiente_de_agrupamento).

## Coeficiente Local

Deve-se primeiramente encontrar o número de vértices vizinhos (k) do vértice base e quantos desses vértices vizinhos formam triângulos entre si (n) tendo o vértice base como um dos vértices  pertencentes desse triângulo. Assim para um grafo não direcional temos k(k-1) combinações de ligações que poderão existir entre os vértices dessa vizinhança, porém temos que remover, dividindo por 2, a dupla contagem das arestas por se tratar de um grafo não direcional.

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/aa96eeedd83d39250c797650d73618ac0335f21b)


![](https://wikimedia.org/api/rest_v1/media/math/render/svg/399ca5503a826bbad56fa5ebd992bb05c230195d)

## Coeficiente Global

Para o Coeficiente Global realiza-se a divisão do somatório dos coeficientes locais de todos vértices pelo número total de vértices:

![](https://wikimedia.org/api/rest_v1/media/math/render/svg/371e6fe890a43feebdae1c8a166ce1a757149872)

## Execução

Basta compilar o arquivo principal main.c que terá como saída um executável exe (Windows) ou out (Unixes)
```
gcc main.c -o main.out
```
E executá-lo
```
// (Windows)
a

// (Unixes / Mac OS X)
chmod a+x a.out
./a.out
```

## Resultados

Ao final da execução, foram encontrados **84 cliques maximais** no grafo em ambas versões do algoritmo. Além disso, também foi achado o Coeficiente de Aglomeração Global igual a **0.25**.

# Licença de Dados

Os dados foram retirados primordialmente da pesquisa **The bottlenose dolphin community of Doubtful Sound features a large proportion of long-lasting associations, Behavioral Ecology and Sociobiology 54, 396-405 (2003).** dos pesquisadores **D. Lusseau, K. Schneider, O. J. Boisseau, P. Haase, E. Slooten, and S. M. Dawson**. 

A compilação dos dados e a manipulação para utilização para teoria de grafos foi feita pela **The Network Data Repository with Interactive Graph Analytics and Visualization** utilizados nesse projeto foram retirados do livro **Proceedings of the Twenty-Ninth AAAI Conference on Artificial Intelligence**, 2015, escrito por **Ryan A. Rossi and Nesreen K. Ahmed**.

Estes dados podem ser encontrados nesse site: [Network Repository](http://networkrepository.com/).

Todos os direitos reservados.