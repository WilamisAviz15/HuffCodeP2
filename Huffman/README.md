# CODIFICAÇÃO DE HUFFMAN

#### O QUE É A CODIFICAÇÃO DE HUFFMAN?

A codificação de Huffman é um método de compressão que usa as probabilidades de ocorrência dos símbolos no conjunto de dados a ser comprimido para determinar códigos de tamanho variável para cada símbolo. Ele foi desenvolvido em 1952 por David A. Huffman que era, na época, estudante de doutorado no MIT, e foi publicado no artigo "A Method for the Construction of Minimum-Redundancy Codes". 

#### COMO QUE FUNCIONA O PROGRAMA? 
Este programa comprime ou extrai arquivos usando a Codificação de Huffman. Na compressão, o arquivo de saída terá nos 3 primeiros bits o número correspondente à quantidade de bits de lixo no final do arquivo. Nos 13 bits
seguintes haverá o número correspondente à quantidade de bytes ocupada pe-
la árvore de Huffman. A árvore de Huffman será escrita após os dois primei-
ros bytes em pré-ordem, em codificação ASCII. Após a árvore de Huffman, ha-
verá os bits com os dados do arquivo comprimido usando a árvore impressa
como codificação. Na descompressão, as regras descritas anteriormente devem
ter sido usadas para comprimir o arquivo de entrada.

#### COMO USAR O PROGRAMA?
Será necessário baixar todos os arquivos da pasta Huffman e compilar a classe main.c em um terminal linux (testado via GCC). Utilize o comando: gcc main.c -o main.out. Após isso, execute o programa com ./main.out. Digite 1 caso seja compressão e 2 caso seja descompressão. Após a escolha da operação, informe o nome do arquivo ou caminho até ele. No final o programa exibe mensagem de sucesso em caso positivo ou erro caso o arquivo não seja encontrado.

#### COMENTANDO AS CLASSES
* main.c: A principal para o programa, pois ela chamará de acordo com a operação do usuário a classe Compress() ou Descompress().

* Compress.c: Ela recebe o nome do arquivo para compressão e realiza os procedimentos necessários para a compressão. É gerado um array de frequencia com todas os caracteres do arquivo de acordo com a tabela ASCII, em seguida criar Nós com o respectivo caractere e frequência adicionando a uma fila de prioridade de acordo com a menor frequência. Logo em seguida, remove da fila os dois elementos de menor prioridade e realiza a soma de suas frequências gerando um novo nó com a soma das frequências, onde o filho à esquerda do novo nó gerado será o primeiro nó removido da fila e o filho à direita do novo nó será o segundo nó removido da fila. Após a operação adiciona o novo nó à fila. Essa operação é realizada até que a fila possua tamanho igual a 1, onde teremos um único nó com a arvore de Huffman totalmente montada. O algoritmo continua no qual pega a árvore de huffman e caminha entre ela, se caminha à esquerda atribui valor 0 e à direita valor 1. Ao chegar em um nó folha printa o caractere e o caminho de bits obtido. Será caminhado na árvore para obter o tamanho dela (quantidade nós existentes). No arquivo comprimido será impresso a árvore em pré-ordem. Ao caminhar por toda a árvore lança os dados em uma Hashtable para ser gerado os novos bytes do arquivo e impressos no arquivo de saída. 

* Descompress.c: Ela recebe o nome do arquivo para descompressão e realiza os procedimentos necessários para descompressão. Do arquivo comprimimdo é obtido o cabeçalho com o lixo e a árvore em pré-ordem. Com a pré ordem montamos a árvore de huffman e em seguida lemos caractere a caractere do arquivo para saber é 0 ou 1, se for 0 estará à esquerda da árvore, se for 1 estará à direita. Quando encontrarmos um nó folha escrevemos o caractere no arquivo de saída descomprimido. Será realizado isso até nao houver mais caracteres a serem lidos no arquivo comprimido.

Na pasta HuffmanTADS estão os Tipos Abstrato de Dados utilizado nas estruturas. Contém os arquivos:
* Huffman.h: Biblioteca criada para armazenar as estruturas: Nodes, Heap e Hash assim como os seus tipos abstratos necessários e propriedades para utilização das estrutruras.
* Functions.h: Biblioteca criada com todas as funções usadas em todo o algoritmo no qual está comentada o que cada função faz e no que é utilizada, serve como documentação para as funções.
