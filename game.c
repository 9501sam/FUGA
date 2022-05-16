#include "game.h"

int eta = 3;     // n like letter
long double alpha = 2;   // a like letter
long double lamda = 0;
long double R[NUM_USERS][NUM_RES_KINDS] = {
    {2, 4, 20},
    {1, 1, 10},
    {2, 2, 10},
};
long double Cmj[NUM_SERVERS][NUM_RES_KINDS] = {
    {4, 8, 40},
    {4, 6, 50},
};
long double PI[NUM_SERVERS][NUM_RES_KINDS] = {// II
    {4, 8, 40},
    {4, 6, 50},
};
long double Cj[NUM_RES_KINDS] = {0};
long double psy[NUM_USERS][NUM_RES_KINDS] = {0}; // Ψ
long double d[NUM_USERS][NUM_RES_KINDS];

void init_game(void)
{
    // init C
    for (int j = 0; j < NUM_RES_KINDS; j++)
        for (int m = 0; m < NUM_SERVERS; m++)
            Cj[j] += Cmj[m][j];
    // init psy
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++)
            psy[i][j] = R[i][j] / Cj[j];
    // init d
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++)
            d[i][j] = psy[i][j] / MAXj_PSYij(i);
    // init lamda
    lamda = 1 / MAXj_SIGMAi_Dij;
}

void set_phi(int com[NUM_SERVERS][NUM_USERS], long double phi[NUM_USERS][NUM_RES_KINDS])
{
    for (int m = 0; m < NUM_SERVERS; m++)
        for (int i = 0; i < NUM_USERS; i++) {
            int num = com[m][i];
            for (int j = 0; j < NUM_RES_KINDS; j++)
                phi[i][j] += (long double) num * R[i][j];
        }
}

void set_A(int coms[NUM_SERVERS][NUM_USERS], long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS])
{
    for (int m = 0; m < NUM_SERVERS; m++)
        for (int i = 0; i < NUM_USERS; i++) {
            int num = coms[m][i];
            for (int j = 0; j < NUM_RES_KINDS; j++)
                A[m][i][j] = (long double) num * R[i][j];
        }
}

long double phi_ij(allocation_decision *A, int i, int j)
{
    long double ret_val = 0.0;
    for (int m = 0; m < NUM_SERVERS; m++)
        ret_val += A->a[m][i][j];
    return ret_val;
}

long double Xij_Cj_lamda_Dij_a_1(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int i, int j)
{
    long double ret_val = 0;
    long double Xij = 0;
    for (int m = 0; m < NUM_SERVERS; m++)
        Xij += A[m][i][j];
    ret_val = Xij / Cj[j] - lamda * d[i][j];
    ret_val = fabs(ret_val);
    ret_val = powl(ret_val, alpha - 1.0);
    return ret_val;
}

long double v(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS]) // TODO
{
    long double ret_val = 0;
    for (int i = 0; i < NUM_USERS; i++)
        for (int j = 0; j < NUM_RES_KINDS; j++) {
            ret_val += Xij_Cj_lamda_Dij_a_1(A, i, j);
        }
    ret_val = powl(ret_val, 1.0 / alpha);
    return ret_val;
    // return powl(SIGMAij(Xij_Cj_lamda_Dij_a_1, A), 1 / alpha);
}

long double u(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int m, int j)
{
    long double SIGMAi_Xmij = 0;
    for (int i = 0; i < NUM_USERS; i++)
        SIGMAi_Xmij += A[m][i][j];
    return 1 - (Cmj[m][j] - SIGMAi_Xmij) / PI[m][j];
}

long double ske(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int m)
{
    long double mean_of_Um = 0;
    for (int j = 0; j < NUM_RES_KINDS; j++)
        mean_of_Um += u(A, m, j);
    mean_of_Um = mean_of_Um / NUM_RES_KINDS;
    long double var = 0;
    for (int j = 0; j < NUM_RES_KINDS; j++)
        var += powl(u(A, m, j) / mean_of_Um - 1, 2);
    return powl(var, 0.5);
}

long double U(long double A[NUM_SERVERS][NUM_USERS][NUM_RES_KINDS], int m) // TODO
{
    return (long double)SGN(1 - alpha) * (long double)v(A) - ske(A, m);
}

// long double _U(int coms[NUM_SERVERS][NUM_USERS], int m)
// {
//     allocation_decision A;
//     for (int m = 0; m < NUM_SERVERS; m++)
//         for (int i = 0; i < NUM_USERS; i++) {
//             int n = coms[m][i];
//             for (int j = 0; j < NUM_RES_KINDS; j++)
//                 A.a[m][i][j] += n * R[i][j];
//         }
//     return ((long double)SGN(1 - alpha) * (long double)v(&A) - ske(&A, m));
// }

// init_game();
// long double f;
// int com[NUM_SERVERS][NUM_USERS] = {
//     {1, 2, 0},
//     {1, 2, 0},
// };
// allocation_decision A;
// for (int m = 0; m < NUM_SERVERS; m++)
//     for (int i = 0; i < NUM_USERS; i++) {
//         int n = com[m][i];
//         for (int j = 0; j < NUM_RES_KINDS; j++)
//             A.a[m][i][j] += n * R[i][j];
//     }
// f = U(&A, 1);
// printf("%f\n", f);
// f = _U(com, 1);
// printf("%f\n", f);
