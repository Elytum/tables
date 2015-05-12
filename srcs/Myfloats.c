#include <Myfloats.h>

t_floats newFloats(int n, ...)
{   
    t_floats    floats;
    va_list     vl;
    int         c; 

    va_start(vl, n);
    va_end(vl);
    floats.len = n;
    if ((floats.values = (float *)malloc(sizeof(float) * n)))
    {
        c = 0;
        while (c < n)
            floats.values[c++] = va_arg(vl, double);
    }
    else
         floats.len = 0;
    return (floats);
}

void    destroyFloats(t_floats *floats)
{
    // (void)floats;
    free(floats->values);
}

void    putFloats(t_floats floats)
{
    int c;

    c = 0;
    dprintf (1, "C = %i, floats.len = %zi\n", c, floats.len);
    while (c < floats.len)
    {
        dprintf(1, "Float in position %i = %f\n", c, floats.values[c]);
        c++;
    }
    dprintf (1, "Done\n");
}
