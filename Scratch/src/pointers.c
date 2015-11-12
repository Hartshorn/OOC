#include <stdio.h>
#include <assert.h>

typedef struct Big {
        int i_val;
        double d_val;
} Big;

void addten(Big *b);

int main()
{
        const char *str = "abc";

        Big b;
        Big *ptr_to_b = &b;

        assert(*str == 'a'),
        assert(str[1] == 'b'),
        assert(*(str + 1) == 'b');
        assert(*(str + 2) == 'c');

        ++str,
        assert(*str == 'b'),
        assert(str[1] == 'c');


        b.i_val = 12,
        assert(b.i_val == 12),
        assert(ptr_to_b->i_val == 12);

        b.d_val = 12.34,
        assert(b.d_val == 12.34),
        assert(ptr_to_b->d_val == 12.34);

        (*ptr_to_b).d_val *= -1,
        assert(b.d_val == -12.34),
        assert(ptr_to_b->d_val != 12.34);

        ptr_to_b->i_val = 100,
        assert(b.i_val == 100),
        assert(ptr_to_b->i_val != 12);

        addten(ptr_to_b),
        assert(b.i_val == 110);

        addten(&b),
        assert(ptr_to_b->i_val == 120);

}

void addten(Big *pb)
{
          pb->i_val += 10;
}
