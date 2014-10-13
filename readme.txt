Documentação do TP 1 de Computação Gráfica
Galaxian
2014/02
Aluno: Renato Utsch Gonçalves

== Compilando
=============
Para compilar o TP, deve-se utilizar o CMake.
Os passos estão a seguir:
1. Extrair o zip do tp para uma nova pasta.
2. Criar uma pasta chamada "build".
3. Navegar até a pasta "build" com o terminal.
4. Executar o comando: "cmake .."
5. Executar o comando: "make"

O executável de nome galaxian será gerado e poderá ser
executado por "./galaxian".

As dependências do programa são no CMake, em um compilador
de C, nas dependências do glfw estarem instaladas (no
ubuntu, têm o nome de xorg-dev and libglu1-mesa-dev),
no OpenGL e na GLUT.

A compilação do jogo foi testada em ambiente
Linux (ArchLinux e Ubuntu), OS X (OS X Mavericks) e
Windows (Windows 7).

Para compilar no linux, é necessário instalar as
bibliotecas que o GLFW depende para compilar e a biblioteca
GLUT.

Instalar a biblioteca FreeGLUT em qualquer um dos sistemas
operacionais ao invés da GLUT original funciona.

Compilação no Windows é simples apenas no Visual Studio,
pois os binários do freeglut que acompanham esse TP e são
utilizados para compilar no windows foram compilados para
o Visual Studio.
Para compilar utilizando o MinGW é preciso suprir sua
implementação da GLUT e possivelmente modificar o script
do CMake.

Um possível guia para tentar instalar a GLUT no windows
segue:
http://web.eecs.umich.edu/~sugih/courses/eecs487/glut-howto/

== Decisões de Implementação
============================
O jogo foi feito em C.
A implementação utilizou a biblioteca GLFW para cuidar das
janelas e do input do usuário e a biblioteca SOIL para
carregar texturas.
A biblioteca GLUT foi utilizada para mostrar texto na tela,
visto que não havia tempo para aprender a utilizar outra
biblioteca.

O código foi dividio internamente em sistemas. Cada objeto
do jogo (definido em objects.h) possuía vários componentes
(definidos na pasta component), e cada componente era 
atualizado pelo seu respectivo sistema (na pasta system).
Por exemplo, o sistema de animation (system/animation.h)
atualizava o componente de animação do Hero e dos Enemies.
O sistema de physics atualizava a posição dos objetos e
testava por colisões. O sistema de renderer desenhava
os objetos na tela.
Com esse design foi possível separar cada tipo de
simulação do jogo: todo o código relacionado a física
ficou em system/physics.c, todo o código relacionado a
input ficou em system/input.c, todo o código relacionado
a animação ficou em system/animation.c, e por aí vai.

Não foi implementado som nem movimento das naves nem tipos
diferentes de naves por falta de tempo.
