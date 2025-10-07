/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

/* Other */
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

int __cdecl compare(const void* a, const void* b) {
    int32_t int_a = *((const int32_t*)a);
    int32_t int_b = *((const int32_t*)b);
    return (int_a > int_b) - (int_a < int_b);
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t ECOCALLMETHOD EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;

    int32_t* bitonicArray = 0;
    int32_t* qsortArray = 0;
    uint32_t len = 0;
    uint32_t i = 0;
    uint32_t power = 0;
    clock_t bitonicStart, bitonicEnd, bitonicTime, qsortStart, qsortEnd, qsortTime;

    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    power = 11;
    while (power <= 24) {
        len = (uint32_t)pow(2, power);
        
        /* Выделение памяти для массивов и заполнение */
        bitonicArray = (int32_t*)pIMem->pVTbl->Alloc(pIMem, len * sizeof(int32_t));
        qsortArray = (int32_t*)pIMem->pVTbl->Alloc(pIMem, len * sizeof(int32_t));
        for (i = 0; i < len; i++) {
            int32_t randomValue = rand();
            bitonicArray[i] = randomValue;
            qsortArray[i] = randomValue;
        }

        bitonicStart = clock();
        pIEcoLab1->pVTbl->BitonicSort(pIEcoLab1, bitonicArray, len, sizeof(int32_t), compare);
        bitonicEnd = clock();
        bitonicTime = bitonicEnd - bitonicStart;

        qsortStart = clock();
        qsort(qsortArray, len, sizeof(int32_t), compare);
        qsortEnd = clock();
        qsortTime = qsortEnd - qsortStart;

        printf("Testing %u elements:\n", len);
        printf("Bitonic sort: %ldms\n", bitonicTime);
        printf("qsort sort: %ldms\n", qsortTime);

        /* Освобождение памяти */
        pIMem->pVTbl->Free(pIMem, bitonicArray);
        pIMem->pVTbl->Free(pIMem, qsortArray);
        bitonicArray = 0;
        qsortArray = 0;

        power++;
    }
    system("Pause");

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

