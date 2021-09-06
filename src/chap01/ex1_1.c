#include <stdio.h>

test_char() {
    char a = 'A';
    char b = '\101';
    char c = '\x41';

    printf("\n===== test_char() =====\n");
    // フォーマット指定子
    // %d: 10進数として出力
    // %c: ASCII 文字として出力
    // %o: 8 進数として出力
    // %x: 16 進数として出力
    printf("(a): %c (%d, %o, %x)", a, a, a, a);
    printf("(b): %c (%d, %o, %x)", b, b, b, b);
    printf("(c): %c (%d, %o, %x)", c, c, c, c);

    // ASCII 文字を文字コードで表現する \xXX という形式で表現する
    printf("A: \x41\n");
}

main() {
    printf("hello, world\"!\n");
    printf("hello, world\t!\n");
    // printf("hello, world\x!\n"); // => compile error
    // error: \x used with no following hex digits
    printf("hello, world\x45!\n"); // ASCII のコード表
}