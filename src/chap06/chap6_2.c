#include <stdio.h>

// リンク先に構造体の使い方をまとめた：https://nukopy.notion.site/0c50c5b8fc72465785ec2583f3758b87

/* その 1：意味はないけど構文的な間違いはないのでコンパイルエラーにならない */
// 「お前なんもやってないやろ」って感じの warning が出力される
/*
struct {
    int a;
    int b;
};
*/

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

// print_point: 構造体 Point の各メンバを出力する関数
void print_point(struct Point p, char *point_name) {
    printf("%s: (%d, %d)\n", point_name, p.x, p.y);
}

void print_rectangle(struct Rectangle rect, char *rect_name) {
    printf(
        "%s:\npt1 (%d, %d)\npt2 (%d, %d)\n",
        rect_name,
        rect.pt1.x,
        rect.pt1.y,
        rect.pt2.x,
        rect.pt2.y
    );
}

// make_point: x および y 座標から点（構造体 Point）を構成する
struct Point make_point(int x, int y) {
    struct Point p = {x, y};
    return p;
}

// add_point: 2 つの点を加算する
struct Point add_point(struct Point p1, struct Point p2) {
    struct Point p = {p1.x + p2.x, p1.y + p2.y};
    return p;
}

// _pt_in_rect: ある点が指定された長方形内に存在するかどうかを判定する（バグを含む）
int _pt_in_rect(struct Point p, struct Rectangle rect) {
    // note: この関数はバグを含む。rect.pt1 の各座標が rect.pt2 の各座標よりも小さいことが保証された状態でしかこの関数は正しい結果を返せない
    return (rect.pt1.x <= p.x && p.x <= rect.pt2.x)
        && (rect.pt1.y <= p.y && p.y <= rect.pt2.y);
}

int pt_in_rect(struct Point p, struct Rectangle rect) {
    return 0;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct Rectangle standardize_rect(struct Rectangle rect) {
    // 長方形の座標を標準形式にする
    // 標準形式：rect.pt1 が左下、rect.pt2 が右上
    struct Rectangle res;

    res.pt1.x = min(rect.pt1.x, rect.pt2.x);
    res.pt1.y = min(rect.pt1.y, rect.pt2.y);
    res.pt2.x = max(rect.pt1.x, rect.pt2.x);
    res.pt2.y = max(rect.pt1.y, rect.pt2.y);

    return res;
}

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

    // test "make_point", "add_point"
    struct Point p1 = make_point(5, 10);
    struct Point p2 = make_point(20, 30);
    struct Point p3 = add_point(p1, p2);
    print_point(p1, "p1");
    print_point(p2, "p2");
    printf("\np3 = add_point(p1, p2):\n");
    print_point(p3, "p3");

    // test "standardize_rect"
    struct Rectangle rect2 = {
        {5, 10},
        {1, 11}
    };
    print_rectangle(rect2, "rect2（標準化前）");
    rect2 = standardize_rect(rect2);
    print_rectangle(rect2, "rect2（標準化後）");

    // 構造体とポインタ K&R p.159 ~
    struct Point origin = {1, 2}, *ptr_origin;
    ptr_origin = &origin;
    printf("\n");

    // 間接参照演算子 "*" による origin のメンバーへのアクセス
    printf("origin: (%d, %d)\n", (*ptr_origin).x, (*ptr_origin).y); // *ptr_origin.x だと演算子の優先度により意図しない結果が返ってくる

    // アロー演算子 "->" による origin のメンバーへのアクセス
    printf("origin: (%d, %d)\n", ptr_origin->x, ptr_origin->y);
}