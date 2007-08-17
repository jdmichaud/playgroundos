#ifndef _INTERRUPT_HANDLER_H_
#define _INTERRUPT_HANDLER_H_

#include "types.h"
#include "defines.h"

void isrFunction0(void);
void isrFunction1(void);
void isrFunction2(void);
void isrFunction3(void);
void isrFunction4(void);
void isrFunction5(void);
void isrFunction6(void);
void isrFunction7(void);
void isrFunction8(void);
void isrFunction9(void);
void isrFunction10(void);
void isrFunction11(void);
void isrFunction12(void);
void isrFunction13(void);
void isrFunction14(void);
void isrFunction15(void);
void isrFunction16(void);
void isrFunction17(void);
void isrFunction18(void);
void isrFunction19(void);
void isrFunction20(void);
void isrFunction21(void);
void isrFunction22(void);
void isrFunction23(void);
void isrFunction24(void);
void isrFunction25(void);
void isrFunction26(void);
void isrFunction27(void);
void isrFunction28(void);
void isrFunction29(void);
void isrFunction30(void);
void isrFunction31(void);


ISRFunction_t isrFunctionTable_g[ISR_TABLE_SIZE] = 
{
  isrFunction0,
  isrFunction1,
  isrFunction2,
  isrFunction3,
  isrFunction4,
  isrFunction5,
  isrFunction6,
  isrFunction7,
  isrFunction8,
  isrFunction9,
  isrFunction10,
  isrFunction11,
  isrFunction12,
  isrFunction13,
  isrFunction14,
  isrFunction15,
  isrFunction16,
  isrFunction17,
  isrFunction18,
  isrFunction19,
  isrFunction20,
  isrFunction21,
  isrFunction22,
  isrFunction23,
  isrFunction24,
  isrFunction25,
  isrFunction26,
  isrFunction27,
  isrFunction28,
  isrFunction29,
  isrFunction30,
  isrFunction31
}

#endif // ! _INTERRUPT_HANDLER_H_
