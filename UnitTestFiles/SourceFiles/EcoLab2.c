#include "CEcoLab2.h"
#include "IEcoInterfaceBus1.h"
#include <stdio.h>

int main(void) {
    CEcoLab2 lab2;
    IEcoInterfaceBus1* pIMgr = 0;

    printf("=== Тест компонента Eco.Lab2 ===\n");

    createInnerComponents(&lab2, pIMgr);
    demo(&lab2);

    printf("=== Завершено ===\n");
    return 0;
}
