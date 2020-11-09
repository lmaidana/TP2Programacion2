#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MAX = 10;

typedef struct Pila
{
  int tope;
  int vector[MAX];
} STR_PILA;

void push(int dato, STR_PILA *pila);
int pop(STR_PILA *pila);
void create(STR_PILA *pila);
bool isEmpty(STR_PILA pila);

int main()
{
  srand(time(NULL));

  STR_PILA pila;
  create(&pila);
  int dato = 0;
  int i = 0;
  char confirmar = 'n';

  printf("Desea agregar un valor aleatorio a su pila? [S/N]: [ ]\b\b");
  scanf(" %c", &confirmar);

  while ((confirmar == 'S' || confirmar == 's') && i < MAX)
  {

    push(rand() % 1000, &pila);
    if (pila.tope < MAX)
    {
      printf("Desea agregar un valor aleatorio a su pila? [S/N]: [ ]\b\b");
      scanf(" %c", &confirmar);
    }
    else
    {
      printf("La pila esta llena,tiene %d elementos\n", pila.tope);
    }
    i++;
  }

  while (!isEmpty(pila))
  {
    dato = pop(&pila);
    printf("valor aleatorio: %d\n", dato);
  }

  return 0;
}

void create(STR_PILA *pila)
{
  pila->tope = 0;
  return;
}

void push(int dato, STR_PILA *pila)
{
  if (pila->tope < MAX)
  {
    pila->vector[pila->tope] = dato;
    (pila->tope)++;
  }
}

bool isEmpty(STR_PILA pila)
{
  return pila.tope == 0;
}

int pop(STR_PILA *pila)
{
  int valor = pila->vector[pila->tope - 1];
  (pila->tope)--;
  return valor;
}