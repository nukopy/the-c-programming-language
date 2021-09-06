#include <stdio.h>

float f2c(float fahr) {
    // Celsius = (Fahrenheit - 32) * 5 / 9
    return (fahr - 32.0) * 5.0 / 9.0;
}

float c2f(float celsius) {
    // Fahrenheit = Celsius * 9 / 5 + 32
    return (celsius) * 9.0 / 5.0 + 32.0;
}

void calc_f2c() {
    int fahr_start = 0;
    int fahr_end = 300;
    int step = 20;
    float celsius;

    printf("Fahrenheit\tCelsius\n");
    for (int fahr = fahr_start; fahr <= fahr_end; fahr += step) {
        celsius = f2c((float)fahr);
        printf("%3d\t%6.1f\n", fahr, celsius);
    }
    printf("\n");
}

void calc_f2c_reverse() {
    int fahr_start = 300;
    int fahr_end = 0;
    int step = 20;
    float celsius;

    printf("Fahrenheit\tCelsius\n");
    for (int fahr = fahr_start; fahr >= fahr_end; fahr -= step) {
        celsius = f2c((float)fahr);
        printf("%3d\t%6.1f\n", fahr, celsius);
    }
}

void calc_c2f() {
    int celsius_start = 0;
    int celsius_end = 300;
    int step = 20;
    float fahr;

    printf("Celsius\tFahrenheit\n");
    for (int celsius = celsius_start; celsius <= celsius_end; celsius += step) {
        fahr = c2f((float)celsius);
        printf("%3d\t%6.1f\n", celsius, fahr);
    }
    printf("\n");
}

main() {
    calc_f2c();
    calc_c2f();
    calc_f2c_reverse();
}