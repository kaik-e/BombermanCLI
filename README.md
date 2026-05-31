# 💣 BomberMan CLI

Projeto desenvolvido para a disciplina de **Programação Imperativa e Funcional** utilizando a linguagem **C** e a biblioteca **Raylib** 🎮

---

# 👨‍💻 Integrantes

* Luis Felipe
* Kaike Campos
* Hugo Diego

---

# 🎯 Sobre o jogo

BomberMan CLI é um jogo inspirado no clássico **Bomberman** 🔥

O jogador deve eliminar todos os inimigos utilizando bombas enquanto evita explosões e colisões.

O jogo possui:

* ✅ Sistema de fases
* ✅ Inimigos com movimentação
* ✅ Colisão
* ✅ Bombas e explosões
* ✅ Destruição de blocos
* ✅ Sistema de vidas ❤️
* ✅ Tela de vitória 🏆
* ✅ Tela de game over ☠️
* ✅ Créditos 🎬
* ✅ Interface fullscreen 🖥️
* ✅ Sistema de ranking por tempo 🏆

---

# 🛠️ Tecnologias utilizadas

* Linguagem C
* Raylib
* Windows / Linux / WSL
* MSYS2 MinGW64

---

# 📁 Estrutura do projeto

```text
BomberManCLI/
│
├── src/
│   ├── main.c
│   ├── render.c
│   ├── bomba.c
│   ├── inimigo.c
│   ├── gameplay.c
│   └── score.c
│
├── include/
│   ├── render.h
│   ├── bomba.h
│   ├── inimigo.h
│   ├── gameplay.h
│   └── score.h
│
├── assets/
│   ├── menu.png
│   ├── player.png
│   ├── inimigo.png
│   ├── parede.png
│   ├── bloco.png
│   ├── chao.png
│   ├── final.png
│   ├── gameover.png
│   └── fasecompleta.png
│
├── slides/
│   └── apresentacao.pdf
│
├── video/
│   └── gameplay.mp4
│
├── Makefile
├── README.md
└── .gitignore
```

---

# 📋 Requisitos

Antes de compilar o projeto é necessário possuir:

* GCC
* Make
* Raylib 5.x
* MSYS2 MinGW64 no Windows

---

# 📦 Instalação da Raylib no Windows

No Windows, abra o terminal **MSYS2 MinGW64** e execute:

```bash
pacman -S mingw-w64-x86_64-raylib
```

Caso seja solicitado, confirme a instalação digitando:

```bash
Y
```

---

# ⚙️ Como compilar

## Windows

Abra o terminal **MSYS2 MinGW64**, navegue até a pasta do projeto e execute:

```bash
make
```

Exemplo:

```bash
cd /c/Users/SEU_USUARIO/Caminho/Para/BomberManCLI
make
```

## Linux / WSL

Abra um terminal na pasta do projeto e execute:

```bash
make
```

---

# ▶️ Como executar

Após a compilação, execute:

```bash
make run
```

Ou diretamente:

## Windows

```bash
./jogo.exe
```

## Linux / WSL

```bash
./jogo
```

---

# 🔧 Compilação manual

Caso não queira usar o Makefile, também é possível compilar manualmente.

## Windows (MSYS2 MinGW64)

```bash
gcc src/main.c src/render.c src/bomba.c src/inimigo.c src/gameplay.c src/score.c -Iinclude -o jogo.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

## Linux / WSL

```bash
gcc src/main.c src/render.c src/bomba.c src/inimigo.c src/gameplay.c src/score.c -Iinclude -o jogo -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

---

# 🎮 Controles

| Tecla  | Ação                |
| ------ | ------------------- |
| W      | Mover para cima     |
| S      | Mover para baixo    |
| A      | Mover para esquerda |
| D      | Mover para direita  |
| ESPAÇO | Colocar bomba 💣    |

---

# 🕹️ Gameplay

O objetivo do jogo é derrotar todos os inimigos de cada fase para avançar até a tela final 🏆

O jogador perde vidas ao tocar inimigos ou ser atingido por explosões ☠️

Ao concluir o jogo, o tempo do jogador é registrado no sistema de ranking.

---

# 🧠 Conceitos utilizados

O projeto utiliza os seguintes conceitos estudados na disciplina:

* ✅ Structs
* ✅ Ponteiros
* ✅ Matrizes
* ✅ Colisão
* ✅ Manipulação gráfica
* ✅ Controle de estados
* ✅ Temporização
* ✅ Modularização
* ✅ Manipulação de arquivos
* ✅ Lista encadeada

---

# 📸 Funcionalidades

* 🔥 Explosões com dano
* 👾 Inimigos inteligentes
* 🧱 Blocos destrutíveis
* 💥 Sistema de bombas
* 🏁 Progressão de fases
* 🎬 Tela de créditos
* 🎨 Interface estilizada
* 🏆 Sistema de ranking por tempo

---

# 🎬 Créditos

## 👨‍💻 Programação

* Luis Felipe
* Kaike Campos
* Hugo Diego

## 🎨 Pixel Arts

* Luis Felipe

## ⚙️ Framework

* Raylib

---

# 📚 Observações

Projeto desenvolvido para fins educacionais 📖

Inspirado no clássico Bomberman 💣🔥