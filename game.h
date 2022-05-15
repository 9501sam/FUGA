#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

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
#define SIGMAij(func, A)                            \
    ({                                              \
        double ret_val = 0;                         \
        for (int i = 0; i < NUM_USERS; i++)         \
            for (int j = 0; j < NUM_RES_KINDS; j++) \
                ret_val += func((A), i, j);         \
        ret_val;                                    \
     })
#define SIGMAi_Xmij(A, m, j)                        \
    ({                                              \
        double ret_val = 0;                         \
        for (int i = 0; i < NUM_USERS; i++)         \
            ret_val += (A)->a[(m)][i][(j)];         \
        ret_val;                                    \
     })
#define Umj_div_Um_1_to_the_pow_of_2(j) \
    ({                                              \
        double ret_val = 0;                         \
        ret_val = u(A, m, j) / mean_of_Um - 1;      \
        ret_val = pow(ret_val, 2);                  \
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
extern double alpha;   // a like letter
extern double lamda;
extern double R[NUM_USERS][NUM_RES_KINDS];
extern double Cmj[NUM_SERVERS][NUM_RES_KINDS];
extern double Cj[NUM_RES_KINDS];
extern double psy[NUM_USERS][NUM_RES_KINDS];
extern double d[NUM_USERS][NUM_RES_KINDS];
extern double PI[NUM_SERVERS][NUM_RES_KINDS];  // II

void init_game(void);
double phi_ij(allocation_decision *A, int i, int j);
double v(allocation_decision *A);
double u(allocation_decision *A, int m, int j);
double ske(allocation_decision *A, int m);
double U(allocation_decision *A, int m);
double _U(int com[NUM_SERVERS][NUM_USERS], int m);

#endif
