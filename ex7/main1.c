#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// 檢查 num 是否已經存在於陣列中（使用指標走訪）
int is_duplicate(int* arr, int count, int num) {
    int* ptr = arr;
    for (int i = 0; i < count; i++) {
        if (*(ptr + i) == num) {
            return 1;
        }
    }
    return 0;
}

// 將前 6 個一般號碼由小到大排序（使用指標交換）
void sort_numbers(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (*(arr + j) > *(arr + j + 1)) {
                int tmp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = tmp;
            }
        }
    }
}

// 產生一組 7 個不重複的樂透號碼（01~69）
void generate_lotto(int* lotto) {
    int count = 0;
    while (count < 7) {
        int num = (rand() % 69) + 1;
        if (!is_duplicate(lotto, count, num)) {
            *(lotto + count) = num;
            count++;
        }
    }
    // 前 6 個號碼排序，第 7 個為特別號維持在最後
    sort_numbers(lotto, 6);
}

int main() {
    int n;
    printf("歡迎光臨長庚樂透彩購買機台\n");
    printf("請問您要買幾組樂透彩:");
    scanf("%d", &n);

    // 限制購買組數為 1 <= n <= 5
    if (n < 1 || n > 5) {
        printf("輸入錯誤，請輸入 1 到 5 之間的數字。\n");
        return 1;
    }

    srand((unsigned int)time(NULL));

    // 取得目前時間並去除換行符號
    time_t curtime;
    time(&curtime);
    char* time_str = ctime(&curtime);
    time_str[strcspn(time_str, "\n")] = '\0';

    FILE* fp = fopen("lotto.txt", "w");
    if (fp == NULL) {
        printf("無法開啟檔案 lotto.txt\n");
        return 1;
    }

    fprintf(fp, "========= lotto649 =========\n");
    fprintf(fp, "= %s =\n", time_str);

    // 固定輸出 5 組欄位
    for (int i = 0; i < 5; i++) {
        fprintf(fp, "[%d]: ", i + 1);
        if (i < n) {
            // 動態配置 7 個 int 空間（符合老師教的 calloc + free 習慣）
            int* lotto = (int*)calloc(7, sizeof(int));
            generate_lotto(lotto);

            for (int j = 0; j < 7; j++) {
                fprintf(fp, "%02d", *(lotto + j));
                if (j < 6) {
                    fprintf(fp, " ");
                }
            }
            fprintf(fp, "\n");

            free(lotto);
            lotto = NULL;
        } else {
            fprintf(fp, "-- -- -- -- -- -- --\n");
        }
    }

    fprintf(fp, "========= csie@CGU =========\n");
    fclose(fp);

    printf("以為您購買的%d組樂透組合輸出至 lotto.txt\n", n);
    return 0;
}
