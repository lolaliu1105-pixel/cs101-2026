#include <stdio.h>
#include <string.h>

// 1. 定義 employee_t 結構體
typedef struct employee {
    int id;
    int age;
    double salary;
    char name[50];
} employee_t;

// 2. 顯示單一員工詳細資訊的函數
void emp_info(employee_t emp) {
    printf("employee id = %d\n", emp.id);
    printf("employee name = %s\n", emp.name);
    printf("employee age = %d\n", emp.age);
    printf("employee salary = %lf\n", emp.salary);
    printf("\n");
}

// 3. 計算平均年齡的函數
int emp_average_age(employee_t emp[], int n) {
    if (n <= 0) return 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += emp[i].age;
    }
    return sum / n;
}

// 4. 將員工資料寫入二進位檔案 (採用老師的指標寫法 p.34)
void emp_writefile(employee_t emp[], int n) {
    FILE* fp = fopen("employee.bin", "wb+");
    if (fp == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fwrite(emp + i, sizeof(employee_t), 1, fp); //[cite: 8]
    }
    fclose(fp);
    return;
}

// 5. 從二進位檔案讀取並印出清單 (採用老師的指標與 while 讀取寫法 p.35)
void emp_readfile(employee_t emp[], int n) {
    FILE* fp = fopen("employee.bin", "rb");
    if (fp == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }
    int i = 0;
    while (fread(emp + i, sizeof(employee_t), 1, fp)) { //[cite: 9]
        printf("[%d] %d %s\n", i, emp[i].id, emp[i].name); //[cite: 9]
        i++; //[cite: 9]
    }
    fclose(fp);
    return;
}

// 6. 主程式 (對應 p.31)
int main() {
    employee_t emp[3];
    
    emp[0].id = 1;
    emp[0].age = 20;
    emp[0].salary = 30000.0;
    strcpy(emp[0].name, "IU");

    emp[1].id = 2;
    emp[1].age = 26;
    emp[1].salary = 36000.0;
    strcpy(emp[1].name, "taylor");

    emp[2].id = 3;
    emp[2].age = 31;
    emp[2].salary = 90000.0;
    strcpy(emp[2].name, "swift");

    // 寫入檔案
    emp_writefile(emp, 3);

    // 宣告讀取用的陣列
    employee_t read_emp[10];
    
    // 讀取檔案並印出簡易清單
    emp_readfile(read_emp, 3);
    printf("\n");

    // 印出詳細的員工資訊 (對應 p.31 右側視窗)
    for (int i = 0; i < 3; i++) {
        emp_info(read_emp[i]);
    }

    return 0;
}
