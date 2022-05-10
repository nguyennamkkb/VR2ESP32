#include "ima.h"
const qint16 Index_Table[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};
/* Quantizer step size lookup table */
const quint16 Step_Table[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};
#define ima_max 16384
#define index_max 80

ima::ima()
{

}
quint8 ima::encoder(qint16 sample)
{quint8 code;               /* ADPCM output value */
qint32 step,diff,diffq,tempstep;           /* Temporary step size */
    step = Step_Table[e_index];
    diff = sample - e_predsample;
    if(diff >= 0) code = 0; else  {code = 8; diff = -diff;}
    tempstep = step;
    if(diff >= tempstep)  {code |= 4; diff -= tempstep;}
    tempstep >>= 1;
    if(diff >= tempstep)  {code |= 2; diff -= tempstep;}
    tempstep >>= 1;
    if(diff >= tempstep)  code |= 1;

    diffq = step >> 3;
    if(code & 4)  diffq += step;
    if(code & 2)  diffq += step >> 1;
    if(code & 1)  diffq += step >> 2;
    if(code & 8)  e_predsample -= diffq;
    else          e_predsample += diffq;
    if(e_predsample > ima_max)        e_predsample = ima_max;
    else if(e_predsample < -ima_max)  e_predsample = -ima_max;
    e_index += Index_Table[code];
    if(e_index < 0)     e_index = 0;
    if(e_index > index_max)    e_index = index_max;
    return (code & 0x0f);
}

qint16 ima::decoder(quint8 code)
{qint32 step,diffq;           /* Temporary step size */
    code &= 0xf;
    step = Step_Table[d_index];
    diffq = step >> 3;
    if(code & 4)  diffq += step;
    if(code & 2)  diffq += step >> 1;
    if(code & 1)  diffq += step >> 2;
    if(code & 8)  d_predsample -= diffq;
    else            d_predsample += diffq;
    if(d_predsample > 32767)  d_predsample = 32767;
    else if(d_predsample < -32767)  d_predsample = -32767;
    d_index += Index_Table[code];
    if(d_index < 0)   d_index = 0;
    if(d_index > 88)    d_index = 88;
    return((qint16)d_predsample);
}
