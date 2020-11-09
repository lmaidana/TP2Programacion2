#include <stdio.h>
#include <stdlib.h>

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
void printPila(STR_PILA pila);

int main()
{
  STR_PILA pila;
  create(&pila);
  int dato = 0;
  int i = 0;
  printf("Ingrese valor a agregar en la pila o 0 para terminar \b");
  scanf(" %d", &dato);
  while (dato != 0 && i < MAX)
  {
    push(dato, &pila);
    if (pila.tope < MAX)
    {
      printf("Ingrese valor a agregar en la pila o 0 para terminar \b");
      scanf(" %d", &dato);
    }
    else
    {
      printf("La pila esta llena,tiene %d elementos\n", pila.tope);
    }
    i++;
  }
  printPila(pila);
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

void printPila(STR_PILA pila)
{
  int dato;
  while (!isEmpty(pila))
  {
    dato = pop(&pila);
    printf("valor ingresado: %d\n", dato);
  }
}