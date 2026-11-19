#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Books {
    int id;
    int price;
    char title[64];
} book_t;

// 計算所有書籍的總價錢（傳入 struct 指標與數量）
int total_price(book_t* books, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        // 使用指標位移與 arrow operator 存取成員
        sum += (books + i)->price;
    }
    return sum;
}

// 輸出所有書籍資料至螢幕（傳入 struct 指標與數量）
void list_books(book_t* books, int n) {
    for (int i = 0; i < n; i++) {
        book_t* ptr = books + i;
        printf("%d %d %s\n", ptr->id, ptr->price, ptr->title);
    }
}

// 將書籍陣列寫入二進位檔 Book.bin
void save_books(const char* filename, book_t* books, int n) {
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("無法開啟檔案 %s 進行寫入\n", filename);
        return;
    }
    fwrite(books, sizeof(book_t), n, fp);
    fclose(fp);
}

// 從二進位檔 Book.bin 讀取書籍資料（參考老師投影片 CJ 34 的寫法）
int read_books(const char* filename, book_t* books) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("無法開啟檔案 %s 進行讀取\n", filename);
        return 0;
    }
    int i = 0;
    book_t tmp;
    while (fread(&tmp, sizeof(book_t), 1, fp)) {
        (books + i)->id = tmp.id;
        (books + i)->price = tmp.price;
        strcpy((books + i)->title, tmp.title);
        i++;
    }
    fclose(fp);
    return i;
}

int main() {
    int n = 6;

    // 1. 建立題目指定的 6 本書籍資料
    book_t init_books[6] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300,  "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550,  "Killers of the Flower Moon"},
        {5, 870,  "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };

    // 2. 將書籍資料儲存至 Book.bin
    save_books("Book.bin", init_books, n);

    // 3. 動態配置記憶體並從 Book.bin 讀回資料驗證
    book_t* my_books = (book_t*)calloc(n, sizeof(book_t));
    if (my_books == NULL) {
        return 1;
    }

    int count = read_books("Book.bin", my_books);

    // 4. 呼叫獨立函式計算總價並印出書單
    printf("Total price: %d\n", total_price(my_books, count));
    list_books(my_books, count);

    // 5. 釋放動態配置的記憶體並設為 NULL
    free(my_books);
    my_books = NULL;

    return 0;
}
