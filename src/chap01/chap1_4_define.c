#define PI 3.14159

main() {
    float x = PI * 2;
    int y = PI * 2;
}

/*
コンパイル
cc -c chap1_4_define.c

プリプロセッサ
cc -E chap1_4_define.c
cc -E chap1_4_define.c > chap1_4_define_preprocessed.c
`#include <stdio.h>` を書くと前処理済みのコードがごちゃごちゃするから、かなりシンプルなソースコードにしてある。
*/

/*
このファイル（chap1_4_define.c）をプリプロセッサで処理すると、以下のようなコードが出力される。
*/

/*
main() {
    float x = 3.14159 * 2;
    int y = 3.14159 * 2;
}
*/

/* 解説
プリプロセッサ命令 #define で定義した記号定数 PI がソースコード内で使われると、プリプロセッサによって 3.14159 に置換される。
なので普通の変数とは性質が異なるということは理解しておいたほうが良い。
実際の前処理済みのソースコードは chap1_4_define_preprocessed.c を参照。
*/
