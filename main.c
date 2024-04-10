#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void troca(int *v, int i, int j);
void quicksort(int *v, int e, int d);
void quicksort_mediana_tres(int *v, int e, int d);
void quicksort_aleatorizado(int *v, int esq, int dir);
void quicksort_tres_partes(int a[], int l, int r);
void imprimi(int *v, int n);
void aleatorio(int *v, int n);
void ordenado(int *v, int n);
void inverso(int *v, int n);
void elementos_repetidos(int *v, int n);

int main(void) {
  srand(time(NULL));
  int *v1,*v2,*v3,*v4;
  int ta = 50000;
  v1 = (int *)malloc(sizeof(int) * ta);
  v2 = (int *)malloc(sizeof(int) * ta);
  v3 = (int *)malloc(sizeof(int) * ta);
  v4 = (int *)malloc(sizeof(int) * ta);
  
  time_t ini, fim;
  double tempo;

  for(int i = 0; i < 4; i++){
    printf("%d elementos ",ta);
    switch(i){
      case 0: printf("aleatorios\n");
        aleatorio(v1, ta);
        aleatorio(v2, ta);
        aleatorio(v3, ta);
        aleatorio(v4, ta);
        break;
      case 1: printf("ordenados\n");
        ordenado(v1, ta);
        ordenado(v2, ta);
        ordenado(v3, ta);
        ordenado(v4, ta);
        break;
      case 2: printf("inverso\n");
        inverso(v1, ta);
        inverso(v2, ta);
        inverso(v3, ta);
        inverso(v4, ta);
        break;
      case 3: printf("repetidos\n");  
        elementos_repetidos(v1, ta);
        elementos_repetidos(v2, ta);
        elementos_repetidos(v3, ta);
        elementos_repetidos(v4, ta);
        break;
    }

      
    ini = clock();
    quicksort(v1, 0, ta - 1);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("Tempo de execuçã basico: %f\n", tempo);
  
    ini = clock();
    quicksort_mediana_tres(v2, 0, ta - 1);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("Tempo de execução mediana de tres: %f\n", tempo);
  
    ini = clock();
    quicksort_aleatorizado(v3, 0, ta - 1);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("Tempo de execução aleatorio: %f\n", tempo);
  
    ini = clock();
    quicksort_tres_partes(v4, 0, ta - 1);
    fim = clock();
    tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
    printf("Tempo de execução tres partes: %f\n", tempo);
}
  
  return 0;
}


void troca(int *v, int i, int j) {
  int aux = v[i];
  v[i] = v[j];
  v[j] = aux;
}

int particao(int *v, int e, int d){
  int pivo, i;
  pivo = e;
  for(i = e + 1; i <= d; i++)
    if(v[i] < v[e]){
      pivo = pivo + 1;
      troca(v, pivo, i);
    }
  troca(v, e, pivo);
  return pivo;
}

void quicksort(int *v, int e, int d){
  int pivo;
  if(e >= d) return;
  pivo = particao(v, e, d);
  quicksort(v, e, pivo - 1);
  quicksort(v, pivo + 1, d);
}

void quicksort_mediana_tres(int *v, int e, int d){
  int pivo;
  if(e >= d) return;
  troca(v, (e + d) / 2, d);
  if(v[e] > v[e+1])
    troca(v, e, e+1);
  if(v[d] < v[e])
    troca(v, d, e);
  if(v[d] < v[e+1])
    troca(v, d, e+1);
  pivo = particao(v, e, d);
  quicksort(v, e, pivo - 1);
  quicksort(v, pivo + 1, d);
}

int pivo_aleatorio(int esq, int dir) { 
  double r;
  r = (double) rand() / RAND_MAX; 
  return(int)(esq+ r*(dir-esq));
}
void quicksort_aleatorizado(int *v, int esq, int dir) {
  int i;
  if(dir <= esq) return;
  troca(v, pivo_aleatorio(esq,dir), esq);
  i = particao(v, esq, dir);
  quicksort_aleatorizado(v, esq, i-1);
  quicksort_aleatorizado(v, i+1, dir);
}

void quicksort_tres_partes(int a[], int l, int r){
  int k, i = l-1, j = r, p = l-1, q = r;
  int v = a[r];
  if(r <= l) return;
  for(;;){
    while(a[++i] < v);
    while(v < a[--j])
      if(j == l) break;
    if(i >= j) break;
    troca(a, i, j);
    if(a[i] == v) {p++; troca(a, p, i);}
    if(v == a[j]) {q--; troca(a, j, q);}
  }
  troca(a, i, r);
  j = i-1;
  i = i+1;
  for(k = l; k <= p; k++, j--) troca(a, k, j);
  for(k = r-1; k >= q; k--, i++) troca(a, i, k);
  quicksort_tres_partes(a, l, j);
  quicksort_tres_partes(a, i, r);
}

void imprimi(int *v, int n){
  for(int i = 0; i < n; i++)
    printf("%d ", v[i]);
  printf("\n");
}
void aleatorio(int *v, int n){
  for(int i = 0; i < n; i++)
    v[i] = rand() % 100;
}
void ordenado(int *v, int n){
  for(int i = 0; i < n; i++)
    v[i] = i;
}
void inverso(int *v, int n){
  for(int i = 0; i < n; i++)
    v[i] = n - i;
}
void elementos_repetidos(int *v, int n) {
  for(int i = 0; i < n; i++) {
    v[i] = i % 10;
  }
}
