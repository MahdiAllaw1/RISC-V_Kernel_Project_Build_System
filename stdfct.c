unsigned long long __umuldi3(unsigned long long x, unsigned long long y)
{
    unsigned long long acc;

    if (x < y) {
        unsigned long long z = x;
        x = y;
        y = z;
    }

    for (acc = 0; y; x <<= 1, y >>= 1)
        if (y & 1)
            acc += x;

    return acc;
}

long long __muldi3(long long x, long long y)
{
    unsigned long long acc, xs, ys;

    if (x < 0) {
        xs = 1;
        x = -x;
    } else
        xs = 0;
    if (y < 0) {
        ys = 1;
        y = -y;
    } else
        ys = 0;

    acc = __umuldi3(x, y);

    return xs ^ ys ? -acc : acc;
}

unsigned long long __udiv_umod_di3(unsigned long long x, unsigned long long y, int opt)
{
    unsigned long long acc, aux;

    if (!y)
        return 0;

    for (aux = 1; y < x && !(y & ((long long)1 << 63)); aux <<= 1, y <<= 1);
    for (acc = 0; x && aux; aux >>= 1, y >>= 1)
        if (y <= x)
            x -= y, acc += aux;

    return opt ? acc : x;
}

long long __udivdi3(long long x, long long y)
{
    return __udiv_umod_di3(x, y, 1);
}

long long __umoddi3(long long x, long long y)
{
    return __udiv_umod_di3(x, y, 0);
}

long long __div_mod_di3(long long x, long long y, int opt)
{
    unsigned long long acc, xs, ys;

    if (!y)
        return 0;

    if (x < 0) {
        xs = 1;
        x = -x;
    } else
        xs = 0;
    if (y < 0) {
        ys = 1;
        y = -y;
    } else
        ys = 0;

    acc = __udiv_umod_di3(x, y, opt);

    if (opt)
        return xs ^ ys ? -acc : acc;
    else
        return xs ? -acc : acc;
}

long long __divdi3(long long x, long long y)
{
    return __div_mod_di3(x, y, 1);
}

long long __moddi3(long long x, long long y)
{
    return __div_mod_di3(x, y, 0);
}

unsigned __umulsi3(unsigned x, unsigned y)
{
    unsigned acc;

    if (x < y) {
        unsigned z = x;
        x = y;
        y = z;
    }

    for (acc = 0; y; x <<= 1, y >>= 1)
        if (y & 1)
            acc += x;

    return acc;
}

int __mulsi3(int x, int y)
{
    unsigned acc, xs, ys;

    if (x < 0) {
        xs = 1;
        x = -x;
    } else
        xs = 0;
    if (y < 0) {
        ys = 1;
        y = -y;
    } else
        ys = 0;

    acc = __umulsi3(x, y);

    return xs ^ ys ? -acc : acc;
}

unsigned __udiv_umod_si3(unsigned x, unsigned y, int opt)
{
    unsigned acc, aux;

    if (!y)
        return 0;

    for (aux = 1; y < x && !(y & (1 << 31)); aux <<= 1, y <<= 1);
    for (acc = 0; x && aux; aux >>= 1, y >>= 1)
        if (y <= x)
            x -= y, acc += aux;

    return opt ? acc : x;
}

int __udivsi3(int x, int y)
{
    return __udiv_umod_si3(x, y, 1);
}

int __umodsi3(int x, int y)
{
    return __udiv_umod_si3(x, y, 0);
}

int __div_mod_si3(int x, int y, int opt)
{
    unsigned acc, xs, ys;

    if (!y)
        return 0;

    if (x < 0) {
        xs = 1;
        x = -x;
    } else
        xs = 0;
    if (y < 0) {
        ys = 1;
        y = -y;
    } else
        ys = 0;

    acc = __udiv_umod_si3(x, y, opt);

    if (opt)
        return xs ^ ys ? -acc : acc;
    else
        return xs ? -acc : acc;
}

int __divsi3(int x, int y)
{
    return __div_mod_si3(x, y, 1);
}

int __modsi3(int x, int y)
{
    return __div_mod_si3(x, y, 0);
}
