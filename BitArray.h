#ifndef BIT_ARRAY
#define BIT_ARRAY

/* Description of internal, underlying storage used by BitArray
 *
 *   wordPositionInArray                             0                                                          1
 *                       ------------------------------------------------------------------------------------------------------------------
 *                     ||       9        |       9        |        9       |  5  ||       9        |       9        |        9       |  5  ||
 *                       ------------------------------------------------------------------------------------------------------------------
 *                       MSB                                                  LSB  MSB                                                  LSB
 *   entryOffsetInWord          0                1                 2                      0                1                 2
 *   position                   1                2                 3                      4                5                 6
 *                                                                         padding                                                   padding
 *
 */

#include "BitArray_utils.h"
#include "BitArray_static.h"
#include "BitArray_dynamic.h"

#endif //#ifndef BIT_ARRAY
