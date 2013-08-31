/*

cp ../../../../native_ref/<target binary> libnetlib.so

gcc -O3 ddottest.c common.c -o ddottest -L. -lnetlib -I../../../../netlib/CBLAS
./ddottest  > ../../../results/mac_os_x-x86_64-ddot-CBLAS.csv

gcc -O3 ddottest.c common.c -o ddottest -I/System/Library/Frameworks/vecLib.framework/Headers -framework veclib
./ddottest  > ../../../results/mac_os_x-x86_64-ddot-veclib.csv

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cblas.h>
#include "common.h"

long benchmark(int size) {
    int m = sqrt(size);
	long requestStart, requestEnd;

    double* a = random_array(m);
    double* b = random_array(m);

	requestStart = currentTimeNanos();

    cblas_ddot(size, a, 1, b, 1);

	requestEnd = currentTimeNanos();

    free(a);
    free(b);

    return (requestEnd - requestStart);
  }

main()
{
	srand(time(NULL));

    double factor = 6.0 / 100.0;
    int i, j;
    for (i = 0 ; i < 10 ; i++) {
        for (j = 1 ; j <= 100 ; j++) {
            int size = (int) pow(10.0, factor * j);
            if (size < 10) continue;
            long took = benchmark(size);
            printf("\"%d\",\"%lu\"\n", size, took);
        }
    }
}