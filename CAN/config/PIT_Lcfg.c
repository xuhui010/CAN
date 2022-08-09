#include "PIT.h"
#include "PIT_Lcfg.h"

void PIT_IntCallBack(void)
{
    CAN_SendCallBack();
}
