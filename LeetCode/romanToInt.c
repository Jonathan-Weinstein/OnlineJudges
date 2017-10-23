#include <stdint.h>

//Symbol 	I 	V 	X 	L 	C 	    D 	    M
//Value 	1 	5 	10 	50 	100 	500 	1,000

int romanToInt(const char* str)
{
    static const unsigned short lut[256]=
    {
        ['I']=1,    ['i']=1,
        ['V']=5,    ['v']=5,
        ['X']=10,   ['x']=10,
        ['L']=50,   ['l']=50,
        ['C']=100,  ['c']=100,
        ['D']=500,  ['d']=500,
        ['M']=1000, ['m']=1000/* everything else = 0 */
    };

    const uint8_t *it = (const uint8_t *)str;
    unsigned res=0u, cur, next = lut[*it++];

    while ((cur=next)!=0u)
    {
        next=lut[*it++];
        res += cur>=next ? cur : -cur;
    }

    return res;
}
