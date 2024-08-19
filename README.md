 __  __ _  ____  ____   __      ___  ____  ____  ____  __ _ 
(  )(  ( \(  __)(  _ \ / _\    / __)(  _ \(  __)(  __)(  ( \
 )( /    / ) _)  )   //    \  ( (_ \ )   / ) _)  ) _) /    /
(__)\_)__)(__)  (__\_)\_/\_/   \___/(__\_)(____)(____)\_)__) 

► Features implementadas:
[x] O heroi tem 100 pontos de vida.
[x] O herói tem uma quantidade limitada de projéteis.
[x] O herói pode se mover em qualquer direção controlado pelo clique do mouse em um local “destino”.
[x] O herói pode sair livremente da base.
[x] O herói pode disparar projéteis pressionando a tecla “Q”. O projétil deve ter um alcance máximo e deve ter a direção apontando para o cursor do mouse no momento do disparo.
[x] Os inimigos surgem nas bordas do mapa aleatoriamente em um intervalo fixo de tempo (que vai diminuindo para aumentar a dificuldade do jogo)
[x] O inimigo caminha em direção ao herói
[x] O inimigo dispara os projéteis sempre em direção ao herói.
[x] Os projéteis podem colidir com o herói, outro inimigo, ou com a base.
[x] A base deve resistir até um número limitado de tiros, podendo regenerar sua estrutura com o tempo
[x] Quando abatido, o inimigo deixa no mapa uma quantidade aleatória limitada de projéteis que pode ser coletada pelo herói se o mesmo passar sobre o item ou esse item desaparece após um determinado tempo caso o herói não o colete.
[x] O jogo deve finalizar se a base conseguir ser protegida por um determinado período de tempo ou se ela for destruída.

► Features EXTRAS implementadas:
[x] O jogo é pausado junto ao timer quando a tecla “P” é apertada


► Informações Gerais das Classes:

Game:
  A classe Game gerencia o loop principal do jogo, incluindo a inicialização da janela, eventos, atualização do estado do jogo e renderização dos elementos na tela. 
  Os métodos incluem initVariables e initWindow para configurar variáveis e a janela do jogo; pollEvents para lidar com entradas do usuário, como teclas e eventos de janela;
  update para atualizar o estado do jogo e seus objetos (jogador, inimigos, base, etc.); e render para desenhar todos os elementos visuais na tela, como o jogador, inimigos
  base e o cronômetro do jogo.

Player:
  A classe Player define o comportamento do jogador no jogo, com métodos para movimentação, colisão e gerenciamento de recursos, como vida e munição.
  Ela possui métodos que atualizam a posição do jogador com base em entradas do teclado e mouse, gerenciam tiros e colisões com objetos e inimigos
  além de renderizar a sprite do jogador e indicadores visuais de vida e munição na tela.

Base:
  A classe Base gerencia a base do jogo, responsável por sua posição, aparência e condição. O método initShape configura a forma e aparência da base, posicionando-a 
  no centro da tela e aplicando uma textura. liferegen permite a regeneração da vida da base a cada dois segundos, enquanto update aplica essa regeneração e ajusta
  a cor da barra de vida conforme a saúde diminui. render desenha a base, sua textura e a barra de vida na tela. receivedamage diminui a vida da base quando atingida,
  os métodos getshape e getvida retornam a forma e o valor atual da vida da base, respectivamente.

EnemySpawnner:
  A classe EnemySpawner é responsável pela criação e manipulação dos inimigos no jogo. O método Enemy_creator gera novos inimigos em posições aleatórias e ajusta 
  o tempo de criação com base no progresso do jogo. set_mira atualiza a posição alvo dos inimigos. update assegura que os "atiradores" estejam sincronizados com 
  os inimigos, enquanto render move os inimigos em direção ao jogador e desenha na tela. setgamerunoff interrompe a criação de inimigos. killenemy remove os inimigos 
  quando atingidos por balas, e damaged_per_bullet verifica se houve colisão de balas com o jogador ou base, retornando dano. getenemies retorna uma lista dos inimigos ativos.

atirador:
  A classe atirador é responsável por controlar os disparos dos inimigos. O método initshape define o formato inicial do atirador. O construtor atirador posiciona o atirador
  com base na posição do inimigo, enquanto o destrutor ~atirador cuida da limpeza dos recursos. O método update está preparado para futuras atualizações do atirador, enquanto
  render desenha as balas na tela e atualiza suas posições. Os métodos get_bullets e get_angles retornam as balas e ângulos dos disparos. O método set_position sincroniza a 
  posição do atirador com a do inimigo. atirando dispara balas em direção à posição do jogador, calculando a trajetória. Por fim, collision_player_check verifica se alguma 
  bala colidiu com o jogador e, em caso positivo, remove a bala e retorna um valor de dano.

GameEnder:
  A classe GameEnder controla a exibição do estado de fim de jogo, seja por derrota ou por limite de tempo. O método initshape configura um ponto central na tela para posicionar 
  a mensagem de fim de jogo. lifetracker verifica se a vida do jogador (p) ou da base (b) chegaram a zero, ou se o tempo de jogo (timer) excedeu 160 segundos. Se qualquer condição
  for atendida, carrega e posiciona uma imagem de "Game Over" no centro da tela e retorna true, indicando que o jogo deve ser pausado. update ajusta a posição da imagem de 
  "Game Over", e render desenha essa imagem na tela quando necessário.



Como Compilar um Jogo Usando SFML no Linux
Instale a SFML:

Abra o terminal e instale a biblioteca SFML com o comando: sudo apt install libsfml-dev

Baixe os Arquivos do Jogo:

Baixe a pasta contendo o código-fonte do jogo, incluindo os arquivos .cpp, os cabeçalhos .h, e as pastas com imagens, áudio e fontes.

Compile o Jogo:

Navegue até a pasta onde os arquivos do jogo estão localizados. Certifique-se de que a SFML está instalada no diretório padrão e, em seguida, execute os seguintes comandos no terminal:

Compile os arquivos .cpp em objetos .o: g++ -c atirador.cpp Base.cpp EnemySpawner.cpp Game.cpp GameEnder.cpp Main.cpp Player.cpp

Linke os arquivos objetos e crie o executável: g++ -o game_project atirador.o Base.o EnemySpawner.o Game.o GameEnder.o Main.o Player.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

Execute o Jogo:

Após a compilação, para rodar o jogo, digite o seguinte comando no terminal: ./game_project

