#include <stdio.h>

void copy_and_print_v1(void) {
    int c;

    c = getchar();
    while (c != EOF) {
        putchar(c);
        c = getchar();
    }
}

/*
C 言語では、代入命令は式として評価される。
つまり、評価された結果が返る。そして、その結果は左辺の変数の評価結果である。
何が言いたいかと言うと、代入命令は単独で記述することができるが、
その評価結果を用いて、別の式に利用できるということである。

例えば、"c = getchar()" という変数への代入は、

1. getchar() がユーザが入力した文字を返す
2. その文字を c に代入する
3. c に代入された文字を評価し、その結果を返す

という順番で評価される。この代入命令の評価結果としては c の値が返る。
C 言語のこの仕組みを使うと、先述したように、代入命令の評価結果を利用してコードをシンプルにすることができる。

例えば、下記の copy_and_print_v2 では v1 の while 文周辺のプログラムを改善し、
コードがよりシンプルになっている。

"(c = getchar()) != EOF" では、"c = getchar()" で変数 c に getchar() で得た文字を代入しつつ、
それがファイルの終端（EOF、End Of File の略）かどうかを調べるということをプログラム 1 行で実現している。
この書き方を多用しすぎると逆にプログラムは逆に読みづらくなるが、適切なポイントで使えれば、読みやすくシンプルなコードが書ける。

なお、注意点として、"c = getchar()" を括弧で括らないいけない、というものがある。
これは、C 言語には演算子の優先順位があるためで、代入演算子 "=" よりも比較演算子 "!=" の方が優先順位が高いためである。

"(c = getchar()) != EOF"

ではなく

"c = getchar() != EOF"（括弧を除去）

とすると、先に "getchar() != EOF" が評価され、
変数 c にはその比較演算の結果として 0 or 1（true or false が整数型に暗黙的にキャストされる）が c に入ってしまう。
入力した文字列が欲しかったので、これは我々の意図とは異なる。演算子の優先順位には注意すべし。

括弧を利用すると、演算子の優先順位を確実にするとともに、その意図を読む人間に伝えることができる。
たとえば、括弧がなくてもある演算が確実に動くとき、括弧を使うことでプログラマの意図がそれを読む人間に伝わり、コードの読みやすさが変わる。

*/

void copy_and_print_v2(void) {
    int c;

    while (((c = getchar()) != EOF)) {
        putchar(c);
    }
}

void test_EOF(void) {
    /*
    EOF の実体は int 型の "-1" である。
    "stdio.h" をインクルードすると、
    プログラムに以下のようなプリプロセッサ命令が組み込まれる。

    #define EOF  (-1)

    そのため、"stdio.h" をインクルードした状態で "EOF" とプログラムに記述した場合、
    "EOF" はプリプロセッサによってコンパイル前に "-1" という整数リテラルに置換される。
    */

    // print getchar() != EOF
    int c;

    // 比較演算子 != の方が優先順位が高いため、変数 c には "getchar() != EOF" の評価結果が代入される
    while (c = getchar() != EOF) { // while ((c = getchar()) != EOF) {
        putchar(c);
    }

    // EOF の値を表示する
    printf("EOF = %d\n", EOF);
}

test_getc_putc() {
    int ch;
    FILE *fp;

    if (fp = fopen("test.txt", "r")) {
        while ((ch = getc(fp)) != EOF) {
            putc(ch, stdout);
            // printf("a");
        }
        fclose(fp);

        return 0;
    } else {
        putc('E', stdout);
    }
}

word_count_v1() {
    long nc;

    nc = 0;
    while (getchar() != EOF)
        ++nc;
    printf("%ld characters was input.\n", nc);
}

word_count_v2() {
    double nc;

    for (nc = 0; getchar() != EOF; ++nc)
        ; // 空の for 文
    printf("%.0f characters was input.\n", nc);
}

FILE *read_file(char* filename) {
    FILE *fp;
    fp = fopen(filename, "r");

    return fp;
}

inspect_file() {
    long n_chs = 0, n_rows = 0, n_spaces = 0, n_tabs = 0;
    int ch;

    // read file
    char *filename = "test.txt";
    FILE *fp = read_file(filename);

    // inspect file
    while((ch = getc(fp)) != EOF) {
        // count characters
        ++n_chs;

        // count rows
        if (ch == '\n')
            ++n_rows;

        // count spaces
        if (ch == ' ')
            ++n_spaces;

        // count tabs
        if (ch == '\t')
            ++n_tabs;
    }

    // report
    printf("Filename  : %s\n", filename);
    printf("----------\n");
    printf("Characters: %6ld\n", n_chs);
    printf("Rows      : %6ld\n", n_rows);
    printf("Spaces    : %6ld\n", n_spaces);
    printf("Tabs      : %6ld\n", n_tabs);
}

main() {
    // copy_and_print_v1();
    // copy_and_print_v2();
    // test_EOF();
    // test_getc_putc();
    // word_count_v1();
    // word_count_v2();
    inspect_file();
}
