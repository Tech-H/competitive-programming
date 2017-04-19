#include "iostream"
#include "stdio.h"
#include "string"
#include "string.h"
#include "algorithm"
#include "math.h"
#include "vector"
#include "map"
#include "queue"
#include "stack"
#include "deque"
#include "set"
using namespace std;

typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
const int inf = 1e9;
const int base = 1e9 +7;
const int MaxN = 1e5+4;

char T[MaxN], P[MaxN]; // T = text, P = pattern
int b[MaxN], n, m; // b = back table, n = length of T, m = length of P

void naiveMatching() {
    for (int i = 0; i < n; i++) { // try all potential starting indices
        bool found = true;
        for (int j = 0; j < m && found; j++) // use boolean flag `found'
            if (i + j >= n || P[j] != T[i + j]) // if mismatch found
                found = false; // abort this, shift starting index i by +1
        if (found) // if P[0 .. m - 1] == T[i .. i + m - 1]
        printf("P is found at index %d in T\n", i);
    }
}

void kmpPreprocess() { // call this before calling kmpSearch()
    int i = 0, j = -1; b[0] = -1; // starting values
    while (i < m) { // pre-process the pattern string P
        while (j >= 0 && P[i] != P[j]) j = b[j]; // if different, reset j using b
            i++; j++; // if same, advance both pointers
        b[i] = j; // observe i = 8, 9, 10, 11, 12 with j = 0, 1, 2, 3, 4
    }
}           // in the example of P = "SEVENTY SEVEN" above

void kmpSearch() { // this is similar as kmpPreprocess(), but on string T
    int i = 0, j = 0; // starting values
        while (i < n) { // search through string T
            while (j >= 0 && T[i] != P[j]) j = b[j]; // if different, reset j using b
                i++; j++; // if same, advance both pointers
        if (j == m) { // a match found when j == m
            printf("P is found at index %d in T\n", i - j);
            j = b[j]; // prepare j for the next possible match
        }
    }
}

int main() {
    strcpy(T, "I DO NOT LIKE SEVENTY SEV BUT SEVENTY SEVENTY SEVEN");
    strcpy(P, "SEVENTY SEVEN");
    n = (int)strlen(T);
    m = (int)strlen(P);

    //if the end of line character is read too, uncomment the line below
    //T[n-1] = 0; n--; P[m-1] = 0; m--;

    printf("T = '%s'\n", T);
    printf("P = '%s'\n", P);
    printf("\n");

    clock_t t0 = clock();
    printf("Naive Matching\n");
    naiveMatching();
    clock_t t1 = clock();
    printf("Runtime = %.10lf s\n\n", (t1 - t0) / (double) CLOCKS_PER_SEC);

    printf("KMP\n");
    kmpPreprocess();
    kmpSearch();
    clock_t t2 = clock();
    printf("Runtime = %.10lf s\n\n", (t2 - t1) / (double) CLOCKS_PER_SEC);

    printf("String Library\n");
    char *pos = strstr(T, P);
    while (pos != NULL) {
        printf("P is found at index %d in T\n", pos - T);
        pos = strstr(pos + 1, P);
    }
    clock_t t3 = clock();
    printf("Runtime = %.10lf s\n\n", (t3 - t2) / (double) CLOCKS_PER_SEC);

    return 0;
}
