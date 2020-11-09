#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int MAX = 10;

typedef struct Cola
{
  int tope; //cantidad de elementos del vector
  int principio;
  int fin;
  int elementos[MAX] = {0}; //vector donde guardamos los valores aleatorios
} STR_COLA;

void crear(STR_COLA *queue);
bool isEmpty(STR_COLA queue);
void add(int valor, STR_COLA *queue);
int remove(STR_COLA *queue);
void print(STR_COLA *ptrQeue);

int main()
{
  STR_COLA cola;
  crear(&cola);
  srand(time(NULL));
  int dato = 0;
  int i = 0;
  char confirmar = 'n';

  printf("Desea agregar un valor aleatorio a su cola? [S/N]: [ ]\b\b");
  scanf(" %c", &confirmar);

  while ((confirmar == 'S' || confirmar == 's') && i < MAX)
  {

    add(rand() % 1000, &cola);
    if (cola.tope < MAX)
    {
      printf("Desea agregar un valor aleatorio a su cola? [S/N]: [ ]\b\b");
      scanf(" %c", &confirmar);
    }
    else
    {
      printf("La cola esta llena,tiene %d elementos\n", cola.tope);
    }

    i++;
  }

  print(&cola);

  return 0;
}

void crear(STR_COLA *queue)
{
  queue->tope = 0;
  queue->principio = 0;
  queue->fin = 0;
}

bool isEmpty(STR_COLA queue)
{
  return queue.tope == 0;
}

void add(int valor, STR_COLA *queue)
{
  if (queue->tope < MAX)
  {
    queue->elementos[queue->tope] = valor;
    (queue->tope)++;
    (queue->fin)++;
  }
}

int remove(STR_COLA *queue)
{
  int valor = queue->elementos[queue->principio];

  for (int i = 0; i < queue->tope; i++)
  {
    queue->elementos[i] = queue->elementos[i + 1];
  }

  (queue->principio) = 0;
  (queue->fin)--;
  (queue->tope)--;

  return valor;
}

void print(STR_COLA *queue)
{
  while (!isEmpty(*queue))
  {
    int valor = remove(queue);
    printf("Valor aleatorio: %d\n", valor);
  }
}