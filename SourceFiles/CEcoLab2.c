#include "CEcoLab2.h"
#include "IEcoInterfaceBus1.h"
#include <stdio.h>

int16_t createInnerComponents(CEcoLab2* me, IEcoInterfaceBus1* pIMgr) {
    int16_t result = 0;

    result = pIMgr->pVTbl->QueryComponent(
        pIMgr,
        &CID_EcoCalculatorB,
        0,
        &IID_IEcoCalculatorX,
        (void**)&me->m_pIX
    );

    if (result != 0 || me->m_pIX == 0) {
        printf("Ошибка: не удалось подключить компонент B.\n");
        return result;
    }

    result = pIMgr->pVTbl->QueryComponent(
        pIMgr,
        &CID_EcoLab1,
        0,
        &IID_IEcoLab1,
        (void**)&me->m_pILab1
    );

    if (result != 0 || me->m_pILab1 == 0) {
        printf("Ошибка: не удалось подключить компонент Lab1.\n");
        return result;
    }

    return 0;
}

void demo(CEcoLab2* me) {
    if (me->m_pIX != 0) {
        int result = me->m_pIX->pVTbl->Addition(me->m_pIX, 3, 5);
        printf("Результат сложения (3 + 5) = %d\n", result);
    } else {
        printf("Компонент IEcoCalculatorX не подключен.\n");
    }
}
