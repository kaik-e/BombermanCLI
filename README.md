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

---

# 🛠️ Tecnologias utilizadas

* Linguagem C
* Raylib
* Linux / WSL

---

# 📁 Estrutura do projeto

```text
BomberManCLI/
│
├── src/
│   └── main.c
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

# ⚙️ Como compilar

```bash
make
```

---

# ▶️ Como executar

```bash
make run
```

---

# 🔧 Compilação manual

```bash
gcc src/main.c -o jogo -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
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

# 🧠 Conceitos utilizados

O projeto utiliza os seguintes conceitos estudados na disciplina:

* ✅ Structs
* ✅ Ponteiros
*  ✅ Matrizes
* ✅ Colisão
* ✅ Manipulação gráfica
* ✅ Controle de estados
* ✅ Temporização

---

# 🕹️ Gameplay

O objetivo do jogo é derrotar todos os inimigos de cada fase para avançar até a tela final 🏆

O jogador perde vidas ao tocar inimigos ou explosões ☠️

---

# 📸 Funcionalidades

* 🔥 Explosões com dano
* 👾 Inimigos inteligentes
* 🧱 Blocos destrutíveis
* 💥 Sistema de bombas
* 🏁 Progressão de fases
* 🎬 Tela de créditos
* 🎨 Interface estilizada

---

# 🎬 Créditos

## 👨‍💻 Programação

* Luis Felipe

## 🎨 Pixel Arts

* Luis Felipe 

## ⚙️ Framework

* Raylib

---

# 📚 Observações

Projeto desenvolvido para fins educacionais 📖

Inspirado no clássico Bomberman 💣🔥
