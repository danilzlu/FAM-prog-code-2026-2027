#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif


#define REPEATS 11

static volatile long long sink = 0;

#define MATRIX_WIDTH  15
#define TIME_WIDTH    16
#define RATIO_WIDTH   10


// Кроссплатформенный бенцмарк
static double now_seconds(void)
{
#ifdef _WIN32
    static LARGE_INTEGER frequency;
    static int initialized = 0;

    LARGE_INTEGER counter;

    if (!initialized) {
        QueryPerformanceFrequency(&frequency);
        initialized = 1;
    }

    QueryPerformanceCounter(&counter);

    return (double) counter.QuadPart /
           (double) frequency.QuadPart;
#else
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (double) ts.tv_sec +
           (double) ts.tv_nsec * 1e-9;
#endif
}


// Создание матрицы
static void fill_matrix(int *a, size_t n)
{
    size_t count = n * n;

    for (size_t i = 0; i < count; ++i)
        a[i] = (int) (i % 100);
}


/* Тестируемые функции */

static long long sum_row_major(const int *a, size_t n)
{
    long long sum = 0;

    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < n; ++j)
            sum += a[i * n + j];

    return sum;
}


static long long sum_column_major(const int *a, size_t n)
{
    long long sum = 0;

    for (size_t j = 0; j < n; ++j)
        for (size_t i = 0; i < n; ++i)
            sum += a[i * n + j];

    return sum;
}


/* Вспомогательные функции */


typedef long long (*sum_function)(const int *, size_t);


static double measure_once(
    sum_function f,
    const int *a,
    size_t n
)
{
    double start = now_seconds();

    long long result = f(a, n);

    double finish = now_seconds();

    sink = result;

    return finish - start;
}


static int compare_double(const void *lhs, const void *rhs)
{
    double a = *(const double *) lhs;
    double b = *(const double *) rhs;

    if (a < b)
        return -1;

    if (a > b)
        return 1;

    return 0;
}


static double median(double *values, int count)
{
    qsort(
        values,
        count,
        sizeof(values[0]),
        compare_double
    );

    return values[count / 2];
}


static double benchmark(
    sum_function f,
    const int *a,
    size_t n
)
{
    double times[REPEATS];

    // Warm-up
    sink = f(a, n);

    for (int i = 0; i < REPEATS; ++i)
        times[i] = measure_once(f, a, n);

    return median(times, REPEATS);
}


// Квадратные матрицы
static void run_test(size_t n)
{
    size_t count = n * n;
    size_t bytes = count * sizeof(int);

    int *a = malloc(bytes);

    if (a == NULL) {
        fprintf(
            stderr,
            "Cannot allocate memory for %zu x %zu matrix\n",
            n,
            n
        );

        return;
    }

    fill_matrix(a, n);

    double row_time =
        benchmark(sum_row_major, a, n);

    double column_time =
        benchmark(sum_column_major, a, n);

    double ratio =
        column_time / row_time;


    /* Красиво печатаем */
    char matrix_name[32];

    snprintf(
        matrix_name,
        sizeof(matrix_name),
        "%zu x %zu",
        n,
        n
    );

    printf(
        "%-15s %16.3f %16.3f %9.2fx\n",
        matrix_name,
        row_time * 1000.0,
        column_time * 1000.0,
        ratio
    );

    free(a);
}



int main(void)
{
    const size_t sizes[] = {
        256,
        512,
        1024,
        2048,
        4096
    };

    const size_t count =
        sizeof(sizes) / sizeof(sizes[0]);

    printf(
        "%-15s %16s %16s %10s\n",
        "Matrix",
        "row-major, ms",
        "column-major, ms",
        "ratio"
    );

    printf(
        "-------------------------------------------------------------\n"
    );

    for (size_t i = 0; i < count; ++i)
        run_test(sizes[i]);

    if (sink == -1)
        printf("%lld\n", sink);

    return 0;
}





