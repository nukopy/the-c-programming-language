#include <stdio.h>

// リンク先に構造体の使い方をまとめた：https://nukopy.notion.site/0c50c5b8fc72465785ec2583f3758b87

/* その 1：意味はないけど構文的な間違いはないのでコンパイルエラーにならない */
// 「お前なんもやってないやろ」って感じの warning が出力される
struct {
    int a;
    int b;
};

/* その 2：構造体とその構造体型の変数の宣言 */
// 構造体自体は使い回せない
struct {
    int a;
    int b;
} myst1, myst2;

/* その 3：構造体タグと共に構造体を定義。構造体タグを使って構造体型の変数を宣言。 */
struct Point {
    int x;
    int y;
};
struct Point point1, point2;

/* その 4：構造体タグ、変数宣言と共に構造体を定義 */
struct _Point {
    int x;
    int y;
} point3, point4;

/* その 5：構造体タグ、変数宣言と共に構造体を定義し、変数を初期化 */
struct __Point {
    int x;
    int y;
} point5 = {1, 2}, point6 = {3, 4};

/* その 6：構造体を入れ子にして定義 */
struct Rectangle {
    struct Point pt1;
    struct Point pt2;
};

/* 代入に関する */
// point_a = {1, 2}; error
// point3 = (struct _Point) {1, 2};

int main(int argc, char *argv[]) {
    // 初期化子を使って構造体を初期化
    struct Point pt = {1, 2};
    printf("%d %d\n", pt.x, pt.y);

    // 代入による初期化
    struct Point pt2;
    printf("初期化前：%d %d\n", pt2.x, pt2.y); // note: 構造体にはゼロ値がある。0 で初期化されることに注意。
    pt2.x = 3;
    pt2.y = 4;
    printf("初期化語：%d %d\n", pt2.x, pt2.y);

    // 入れ子の構造体
    struct Rectangle rect = {
        {1, 2},
        {3, 4}
    };
    printf("\nstruct Rectanble rect:\n");
    printf("pt1: (%d, %d)\n", rect.pt1.x, rect.pt1.y);
    printf("pt2: (%d, %d)\n", rect.pt2.x, rect.pt2.y);
}