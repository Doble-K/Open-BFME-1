// cl: /DNDEBUG /MD /EHsc /Ob1 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "wwstring.h"
#define MUTEX_H
#include "../../../../../reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mempool.h"
#include "hanim.h"

template HAnimComboDataClass *
ObjectPoolClass<HAnimComboDataClass, 256>::Allocate_Object_Memory(void);
