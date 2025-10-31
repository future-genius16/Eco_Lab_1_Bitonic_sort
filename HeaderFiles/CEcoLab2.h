#ifndef __C_ECOLAB2_H__
#define __C_ECOLAB2_H__

#include "IEcoLab2.h"
#include "IEcoCalculatorX.h"
#include "IEcoLab1.h"

typedef struct CEcoLab2 {
    IEcoLab2VTbl* pVTbl;
    uint32_t m_cRef;
    IEcoUnknownVTbl* m_pISys;
    IEcoUnknownVTbl* m_pOuterUnknown;

    IEcoCalculatorX* m_pIX;
    IEcoLab1* m_pILab1;
} CEcoLab2;

int16_t createInnerComponents(CEcoLab2* me, IEcoInterfaceBus1* pIMgr);
void demo(CEcoLab2* me);

#endif /* __C_ECOLAB2_H__ */
