# recodese
Algoritmos para Reconhecimento e Classificação de Desenhos Feitos à Mão

Este projeto é dedicado ao reconhecimento de desenhos à mão livre feitos em uma folha branca de papel. Ele compôs um projeto de pesquisa em Narrativas Interativas, onde desenhos eram utilizados como forma de interação. Para mais informações, consulte [Paper and Pencil Interactive Storytelling
Based on Generic Hand-drawn Sketches
](http://www.sbgames.org/sbgames2017/papers/ComputacaoShort/174585.pdf).

A metodologia empregada para o reconhecimento e classificação dos desenhos se deu em três etapas:
1) Processamento de imagens
2) Extração de características
3) Aplicação de algoritmos de aprendizagem de máquina

Este projeto é composto por uma biblioteca de reconhecimento de desenhos em C++ responsável pelas etapas 1 e 2, além de um servidor de classificação de desenhos em Java responsável pela etapa 3.

## Aplicação

Definimos aqui um vocabulário de desenhos reconhecíveis, sendo eles: (a) nuvens, (b) cristais de gelo, (c) fogueiras, (d) muros, (e)buracos e (f) rios. Este vocabulário pode ser facilmente extendido ou modificado, bastando ao usuário alimentar o sistema com imagens dos desenhos desejados para a obtenção de suas características através da biblioteca de reconhecimento e, então, usar tais características para elaborar um classificador de sua preferência (árvore de decisão, redes neurais, etc) a ser utilizado no servidor de classificação.
