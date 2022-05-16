#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#define error   0.01
#define almost_eq(x, y) ((-error < ((long double)(x) - (long double)(y))) && (((long double)(x) - (long double)(y)) < error))
#define MAX(x, y)       ((x) > (y)) ? (x) : (y)
#define NUM_USERS       3   // {i | 1, 2, ..., s}
#define NUM_RES_KINDS   3   // {j | 1, 2, ..., k}
#define NUM_SERVERS     2   // {m | 1, 2, ..., p}
#define NUM_VM_TYPES    NUM_USERS
#define MAXj_PSYij(i)                               \
    ({                                              \
        double ret_val = 0;                         \
        for (int j = 0; j < NUM_RES_KINDS; j++)     \
            ret_val = MAX(ret_val, psy[(i)][j]);    \
        ret_val;                                    \
    })
#define SIGMAi_Dij(j)                               \
    ({                                              \
        double ret_val = 0;                         \
        for(int i = 0; i < NUM_USERS; i++)          \
            ret_val += d[i][(j)];                   \
        ret_val;                                    \
     })

#define MAXj_SIGMAi_Dij                             \
    ({                                              \
        double ret_val = 0;                         \
        for (int j = 0; j < NUM_RES_KINDS; j++)     \
            ret_val = MAX(ret_val, SIGMAi_Dij(j));  \
        ret_val;                                    \
     })
#define Umj_div_Um_1_to_the_pow_of_2(j) \
    ({                                              \
        double ret_val = 0;                         \
        ret_val = u(A, m, j) / mean_of_Um - 1;      \
        ret_val = powl(ret_val, 2);                  \
        ret_val;                                    \
     })

#define SIGMAj(func)                                \
    ({                                              \
        double ret_val = 0;                         \
        for (int j = 0; j < NUM_RES_KINDS; j++)     \
            ret_val += func(j);                     \
        ret_val;                                    \
     })
#define SGN(num) (((num) == 0) ? (0) : (((num) > 0) ? 1 : -1))
typedef enum {
    CPU,
    MEM,
    DISK,
} resource;

typedef struct {
    double a[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS];
} allocation_decision;

extern int eta;     // n like letter
extern long double alpha;   // a like letter
extern long double lamda;
extern long double R[NUM_USERS][NUM_RES_KINDS];
extern long double Cmj[NUM_SERVERS][NUM_RES_KINDS];
extern long double Cj[NUM_RES_KINDS];
extern long double psy[NUM_USERS][NUM_RES_KINDS];
extern long double d[NUM_USERS][NUM_RES_KINDS];
extern long double PI[NUM_SERVERS][NUM_RES_KINDS];  // II

void init_game(void);
void set_phi(int coms[NUM_SERVERS][NUM_USERS], long double phi[NUM_USERS][NUM_RES_KINDS]);
void set_A(int coms[NUM_SERVERS][NUM_USERS], long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS]);

long double phi_ij(allocation_decision *A, int i, int j);
long double Xij_Cj_lamda_Dij_a_1(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int i, int j);
long double v(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS]);
long double u(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int m, int j);
long double ske(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int m);
long double U(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int m);

#endif
