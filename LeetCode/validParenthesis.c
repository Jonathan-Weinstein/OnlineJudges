#include <stdbool.h>
/*
    This solution is interesting because it uses the already read
    part of the string as space for a stack, instead of allocating separate memory.
    It also does this even after a sentinel is placed at the beginning of the string,
    to avoid also checking if the stack is empty on encountering a closing brace.
    Problem didn't say couldn't modify string, so trying to do whats asked with minimal work.
*/
bool isValid(char *it)//zero byte sentinel at end
{
    unsigned ch = *it;

    if (ch!='\0')
    {
        char *const beforeStack=it;
        char *stkEnd=it+1;//past last item pushed. PUSH: *top++ = ch; POP: = *--top;
        unsigned nextCh;
        *beforeStack='\0';//so don't also have to check if stack is empty when encounter closing

        do
        {
            nextCh = *++it;
            switch (ch)
            {
                case '(': case '[': case '{': *stkEnd++ = ch; break;

                case ')': if (*--stkEnd != '(') return false; break;
                case ']': if (*--stkEnd != '[') return false; break;
                case '}': if (*--stkEnd != '{') return false; break;
            }
        }
        while ((ch=nextCh)!='\0');

        return stkEnd == beforeStack+1;
    }
    else
        return true;
}
