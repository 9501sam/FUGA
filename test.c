#include "game.h"

void test_init_game(void)
{
    init_game();
    assert(0.34 < lamda && lamda < 0.348);
}

int main()
{
    test_init_game();
    double f;
    int com[NUM_SERVERS][NUM_USERS] = {
        {1, 2, 0},
        {1, 2, 0},
    };
    allocation_decision A;
    for (int m = 0; m < NUM_SERVERS; m++)
        for (int i = 0; i < NUM_USERS; i++) {
            int n = com[m][i];
            for (int j = 0; j < NUM_RES_KINDS; j++)
                A.a[m][i][j] += n * R[i][j];
        }
    f = U(&A, 1);
    printf("%f\n", f);
    f = _U(com, 1);
    printf("%f\n", f);
    return 0;
}
