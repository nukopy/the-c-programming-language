#include <stdio.h>

#define IN 1 // 単語の中
#define OUT 0 // 単語の外

FILE *read_file(char *filename);
int is_not_word_char(char c);
int is_symbol(char c);
void ex1_12_word_count(char *filename);

main() {
    char *filename = "test.txt";

    // K&R p.27
    // 演習 1-12: 入力した単語を 1 行に 1 つずつ出力するプログラムを書け。
    // 実行結果はこのファイル（ex1_12.c の末尾にコメントで残してある）
    ex1_12_word_count(filename);
}

/* functions */

FILE *read_file(char *filename) {
    FILE *fp = fopen(filename, "r");

    return fp;
}

int is_not_word_char(char c) {
    // 文字が空白、タブ、改行か否かを判定する
    if (c == ' ' || c == '\t' || c == '\n')
        return 1;
    else
        return 0;
}

int is_symbol(char c) {
    // 文字が記号か否かを判定する
    if (c == ',' || c == '.' || c == '!' || c == '?')
        return 1;
    else
        return 0;
}

void ex1_12_word_count(char *filename) {
    // 単語をカウントし、その単語を出力する
    // 単語の定義：空白、タブ、改行を除く連続した文字列
    long n_chars = 0, n_words = 0;
    int c;

    // read file
    FILE *fp = read_file(filename);

    printf("Filename  : %s\n", filename);
    printf("----------\n");
    printf("Words ↓\n");

    int state = 0;
    while ((c = getc(fp)) != EOF) {
        // count chars
        ++n_chars;

        // count words
        if (is_not_word_char(c)) {
            // 現在の文字が空白、タブ、改行のとき
            if (state == OUT) {
                // 既に state = 0（つまり、1 つ前の文字が空白、タブ、改行のとき）
                // 空白、タブ、改行が連続している状態
                // state: 0 => 0（変化なし）
                ;
            } else {
                // state == 1（つまり、1 つ前の文字が空白、タブ、改行以外の文字だったとき）
                // state: 1 => 0（文字 => not 単語の文字）
                printf("\n");
                ++n_words;
                state = OUT;
            }
        } else {
            if (is_symbol(c))
                // 記号 ','、'.'、'!'、'?' のときは単語に関係ないので出力しない
                ;
            else
                putc(c, stdout);

            // 現在の文字が空白、タブ、改行でないとき
            if (state == IN)
                // 既に state = 1（つまり、1 つ前の文字が空白、タブ、改行以外の文字だったとき）
                // state: 1 => 1（変化なし）
                ;
            else
                // state = 0（つまり、1 つ前の文字が空白、タブ、改行のとき）;
                // state: 0 => 1（not 単語の文字 => 文字）
                state = IN;
        }
    }
    // もし EOF の直前が単語のとき、state = 1 のままなのでカウントが更新されない。
    // それを補正するために、EOF まで読み込んだ後に state = 1 ならこれをカウントする。
    if (state == IN)
        ++n_words;

    fclose(fp);

    // print stats
    printf("\n");
    printf("\n----------\n");
    printf("Stats\n");
    printf("Characters : %6ld\n", n_chars);
    printf("Words      : %6ld\n", n_words);
}

/* 実行結果 */

// 入力したファイル：test.txt
/*
Hi, how are you?
I'm good, thanks.
END   OF    FILE  desuyo hoge
*/

// 出力
/*
Filename  : test.txt.out
----------
Words ↓
Hi
how
are
you
I'm
good
thanks
END
OF
FILE
desuyo
hoge

----------
Stats
Characters :     64
Words      :     12
*/