#include <stdio.h>

#define IN 1 // 単語の中
#define OUT 0 // 単語の外

void print_file(char *filename) {
    FILE *fp = read_file(filename);

    printf("Filename  : %s\n", filename);
    printf("----------\n");
    printf("Content ↓\n");

    int c;
    while ((c = getc(fp)) != EOF) {
        putchar(c);
    }
    printf("\n\n");

    fclose(fp);
}

void word_count(char *filename) {
    // 単語をカウントする
    // 単語の定義：空白、タブ、改行を除く連続した文字列
    long n_chars = 0, n_words = 0;
    int c;

    // read file
    FILE *fp = read_file(filename);

    printf("Filename  : %s\n", filename);
    printf("----------\n");
    printf("Content ↓\n");

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

                // 文字は出力しない（空白が連続するような出力をしない）
                // putc(c, stdout);  // これをコメントインすると、連続した空白が出力される
                ;
            } else {
                // state == 1（つまり、1 つ前の文字が空白、タブ、改行以外の文字だったとき）
                // state: 1 => 0（文字 => not 単語の文字）
                putc(c, stdout);

                ++n_words;
                state = OUT;
            }
        } else {
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

main() {
    char *filename = "test.txt";

    print_file(filename);
    word_count(filename);
}

/*
print_file は、ファイルの内容をそのまま加工せずに表示する。
word_count では、重複する空白は除去して出力するようになっている。
その出力が以下。

```
Filename  : test.txt
----------
Content ↓
Hi, how are you?
I'm good, thanks.
END   OF    FILE  desuyo hoge

Filename  : test.txt
----------
Content ↓
Hi, how are you?
I'm good, thanks.
END OF FILE desuyo hoge

----------
Stats
Characters :     64
Words      :     12
```

*/