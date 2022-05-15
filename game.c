#include "game.h"

int eta = 3;     // n like letter
double alpha = 2;   // a like letter
double lamda = 0;
double R[NUM_USERS][NUM_RES_KINDS] = {
    {2, 4, 20},
    {1, 1, 10},
    {2, 2, 10},
};
double Cmj[NUM_SERVERS][NUM_RES_KINDS] = {
    {4, 8, 40},
    {4, 6, 50},
};
double PI[NUM_SERVERS][NUM_RES_KINDS] = {// II
    {4, 8, 40},
    {4, 6, 50},
};
double Cj[NUM_RES_KINDS] = {0};
double psy[NUM_USERS][NUM_RES_KINDS] = {0}; // Ψ
double d[NUM_USERS][NUM_RES_KINDS];

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

double phi_ij(allocation_decision *A, int i, int j)
{
    double ret_val = 0.0;
    for (int m = 0; m < NUM_SERVERS; m++)
        ret_val += A->a[m][i][j];
    return ret_val;
}

double Xij_Cj_lamda_Dij_a_1(allocation_decision *A, int i, int j)
{
    double ret_val = 0;
    double Xij = 0;
    for (int m = 0; m < NUM_SERVERS; m++)
        Xij += A->a[m][i][j];
    ret_val = Xij / Cj[j] - lamda * d[i][j];
    ret_val = fabs(ret_val);
    ret_val = pow(ret_val, alpha - 1);
    return ret_val;
}

double v(allocation_decision *A)
{
    return pow(SIGMAij(Xij_Cj_lamda_Dij_a_1, A), 1 / alpha);
}

double u(allocation_decision *A, int m, int j)
{
    return 1 - (Cmj[m][j] - SIGMAi_Xmij(A, m, j)) / PI[m][j];
}

double ske(allocation_decision *A, int m)
{
    double mean_of_Um = 0;
    for (int j = 0; j < NUM_RES_KINDS; j++)
        mean_of_Um += u(A, m, j);
    mean_of_Um = mean_of_Um / NUM_RES_KINDS;
    return pow(SIGMAj(Umj_div_Um_1_to_the_pow_of_2), 0.5);
}

double U(allocation_decision *A, int m)
{
    return (SGN(1 - alpha) * v(A) - ske(A, m));
}

double _U(int com[NUM_SERVERS][NUM_USERS], int m)
{
    allocation_decision A;
    for (int m = 0; m < NUM_SERVERS; m++)
        for (int i = 0; i < NUM_USERS; i++) {
            int n = com[m][i];
            for (int j = 0; j < NUM_RES_KINDS; j++)
                A.a[m][i][j] += n * R[i][j];
        }
    return (SGN(1 - alpha) * v(&A) - ske(&A, m));
}
