#include <limits.h>
#include <ctype.h>

#if -(INT_MIN + 1) != 0x7fffffff
#error want 32 bit twos complement
#endif

#define UINT_BILLION 1000000000u//ten digits, 9 zeros

typedef struct
{
    union
    {
        unsigned u;
        unsigned i;
    };
    const char *past;
} atou_result;

atou_result atou_noskip_nosign(const char *p)
{
    atou_result res={0u, p};
    unsigned udig;
    for (; (udig=(const unsigned char)*res.past-48u) < 10u; ++res.past)
    {
        res.u = res.u*10u + udig;
    }

    return res;
}

int myAtoi(const char* f)//first
{
    unsigned char uc;

    while (isspace(uc=*f))
        ++f;

    if (uc=='-')
    {
        do ++f; while (*f=='0');//skip the '-' always

        atou_result r=atou_noskip_nosign(f);
        unsigned len = r.past-f;

        if (len<10u)
            return -r.i;
        else if (len==10u && r.u >= UINT_BILLION)//if didn't carry and wrap around
            return (r.u <= -(unsigned)INT_MIN) ? -r.i : INT_MIN;
        else
            return INT_MIN;//too many digits, not counting leading zeros;
    }
    else
    {
        if (uc=='+') ++f;
        while (*f=='0') ++f;

        atou_result r=atou_noskip_nosign(f);
        unsigned len = r.past-f;

        if (len<10u)
            return r.u;
        else if (len==10u && r.u >= UINT_BILLION)//if didn't carry and wrap around
            return r.u<=(unsigned)INT_MAX ? r.i : INT_MAX;//and wouldn't overflow signed interp
        else
            return INT_MAX;//too many digits, not counting leading zeros;
    }
}
