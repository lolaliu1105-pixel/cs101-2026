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

// 4. 將員工資料寫入二進位檔案 (employee.bin)
void emp_writefile(employee_t emp[], int n) {
    FILE *file = fopen("employee.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fwrite(emp, sizeof(employee_t), n, file);
    fclose(file);
}

// 5. 從二進位檔案讀取員工資料
void emp_readfile(employee_t emp[], int n) {
    FILE *file = fopen("employee.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }
    fread(emp, sizeof(employee_t), n, file);
    fclose(file);
}

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

    // 宣告讀取用的陣列並讀出檔案內容
    employee_t read_emp[10];
    emp_readfile(read_emp, 3);

    // 【新增】印出像投影片右上角那樣的簡易清單格式
    for (int i = 0; i < 3; i++) {
        printf("[%d] %d %s\n", i, read_emp[i].id, read_emp[i].name);
    }
    printf("\n");

    // 印出詳細的員工資訊
    for (int i = 0; i < 3; i++) {
        emp_info(read_emp[i]);
    }

    return 0;
}
