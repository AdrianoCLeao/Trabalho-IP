# Essa merda ta funcionando tudo que foi pedido

## Ainda falta:
To c um problemao na hora de ler a string de genero, deve ser um detalhe na leitura q eu fiz merda e nao sei onde ta o erro. Fora isso ta tudo certo.

## Funções

**`registrarTexto(const char arquivo, const char texto)**

**Descrição:** Adiciona uma entrada de log formatada com data e hora em um arquivo especificado.

**Parâmetros:**
- `arquivo`: Nome do arquivo onde será escrito o log.
- `texto`: Conteúdo do texto a ser registrado.

**Uso:** Usado para registrar adições e remoções de jogos.

**`lerString(const char prompt)**

**Descrição:** Lê uma entrada de string do usuário.

**Parâmetro:** `prompt`: Mensagem de prompt exibida para o usuário.

**Retorna:** String alocada dinamicamente contendo a entrada do usuário.

**`adicionarJogo(Jogo *jogos, int count)**

**Descrição:** Adiciona um novo jogo à coleção.

**Parâmetros:**
- `jogos`: Ponteiro para o array de jogos (Jogo) alocado dinamicamente.
- `count`: Ponteiro para o contador de jogos.

**Uso:** Solicita detalhes do jogo ao usuário (nome, preço, gênero, classificação e quantidade) e registra a adição com uma marca de tempo.

**`removerCopias(Jogo jogos, int count)**

**Descrição:** Remove cópias de um jogo da coleção.

**Parâmetros:**
- `jogos`: Array de jogos.
- `count`: Contagem de jogos.

**Uso:** Solicita ao usuário o nome do jogo e o número de cópias a serem removidas. Registra a ação de remoção com uma marca de tempo.

**`procurarJogoPorNome(Jogo lista, int count, const char nome)**

**Descrição:** Procura um jogo pelo nome na coleção.

**Parâmetros:**
- `lista`: Array de jogos.
- `count`: Contagem de jogos.
- `nome`: Nome do jogo a ser procurado.

**Uso:** Imprime detalhes do jogo se encontrado, caso contrário, notifica que o jogo não foi encontrado.

**`gerarRelatorioPorCategoria(Jogo jogos, int count, const char categoria, const char* valor)**

**Descrição:** Gera um relatório de jogos filtrados por categoria (gênero ou classificação).

**Parâmetros:**
- `jogos`: Array de jogos.
- `count`: Contagem de jogos.
- `categoria`: Filtro de categoria (gênero ou classificação).
- `valor`: Valor do filtro de categoria.

**Uso:** Lista jogos que correspondem à categoria e valor especificados.

**`gerarRelatorioPorData(Jogo jogos, int count)**

**Descrição:** Gera um relatório de jogos agrupados por data de adição.

**Parâmetros:**
- `jogos`: Array de jogos.
- `count`: Contagem de jogos.

**Uso:** Exibe jogos ordenados pela data de adição, listando os jogos adicionados em cada data única.

