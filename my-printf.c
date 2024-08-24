#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int my_putchar(char c){
    write(1, &c, 1);
    return 1;
}

int put_str(char *str){
    int count = 0;
    int i = 0;
    while(str[i] != '\0'){
        count += my_putchar(str[i]);
        i++;
    }
    return count;
}

int my_strlen(char *len){
    int i = 0;
    while(len[i] != '\0'){
        i++;
    }
    return i;
}

char *my_reverse(char *p1){
    char c;
    int len = my_strlen(p1);
    int i = 0;
    while(i < len / 2){
        c = p1[len - i - 1];
        p1[len - i - 1] = p1[i];
        p1[i] = c;
        i++;
    }
    return p1;
}

char *my_itoa(long num, char *str, int base){
    int i = 0;
    if(num < 0){
        str[i++] = '-';
        num = -num;
    }
    int j = i;
    while(num > 0){
        if((num % base) < 10){
            str[i++] = (num % base) + '0';
        }else{
            str[i++] = (num % base) - 10 + 'a';
        }
        num /= base;
    }
    return my_reverse(&str[j]);
}

char *my_unsigned(unsigned num, char *str, int base){
    int i = 0;
    while(num > 0){
        if((num % base) < 10){
            str[i++] = (num % base) + '0';
        }else{
            str[i++] = (num % base) - 10 + 'a';
        }
        num /= base;
    }
    return my_reverse(str);
}

int my_printf_d(int num) {
    char num_str[12] = {0};
    my_itoa(num, num_str, 10);
    return put_str(num_str);
}

int my_printf_o(long num) {
    char num_str[21] = {0};
    my_itoa(num, num_str, 8);
    return put_str(num_str);
}

int my_printf_u(unsigned num) {
    char num_str[12] = {0};
    my_unsigned(num, num_str, 10);
    return put_str(num_str);
}

int my_printf_x(long num) {
    char num_str[21] = {0};
    my_itoa(num, num_str, 16);
    return put_str(num_str);
}

int my_printf_c(char c) {
    return my_putchar(c);
}

int my_printf_s(char *str) {
    return put_str(str);
}

int my_printf_p(long num) {
    char num_str[21] = {0};
    my_itoa(num, num_str, 16);
    int count = put_str("0x");
    count += put_str(num_str);
    return count;
}

int my_printf(char *str, ...){
    va_list my_list;
    va_start(my_list, str);
    int count = 0;
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] == '%'){
            i++;
            if(str[i] == 'd'){
                count += my_printf_d(va_arg(my_list, int));
            }else if(str[i] == 'o') {
                count += my_printf_o(va_arg(my_list, long));
            }else if(str[i] == 'u') {
                count += my_printf_u(va_arg(my_list, unsigned));
            }else if(str[i] == 'x') {
                count += my_printf_x(va_arg(my_list, long));
            }else if(str[i] == 'c') {
                count += my_printf_c(va_arg(my_list, int));
            }else if(str[i] == 's') {
                count += my_printf_s(va_arg(my_list, char *));
            }else if(str[i] == 'p') {
                count += my_printf_p(va_arg(my_list, long));
            }
        }else{
            count += my_putchar(str[i]);
        }
        i++;
    }
    va_end(my_list);
    return count;
}

int main(){
    int num = 12345678;
    char str[] = "hello world";
    char c = 'a';

    my_printf("\t---P---\nmy Printf: %p\n", &num);
    printf("org Printf: %p\n", &num);

    my_printf("\t---o---\nmy Printf: %o\n", num);
    printf("org Printf: %o\n", num);

    my_printf("\t---x---\nmy Printf: %x\n", num);
    printf("org Printf: %x\n", num);

    my_printf("\t---d---\nmy Printf: %d\n", -num);
    printf("org Printf: %d\n", -num);

    my_printf("\t---c---\nmy Printf: %c\n", c);
    printf("org Printf: %c\n", c);

    my_printf("\t---s---\nmy Printf: %s\n", str);
    printf("org Printf: %s\n", str);

    my_printf("\t---u---\nmy Printf: %u\n", -num);
    printf("org Printf: %u\n", -num);

    my_printf("\t---u---\nmy Printf: %u\n", num);
    printf("org Printf: %u\n", num);

    my_printf("\t---Length test---\n");

    int len_my_printf = my_printf("Test length: %d\n", -1234567890);
    int len_org_printf = printf("Test length: %d\n", -1234567890);

    printf("\nLength my Printf: %d\n", len_my_printf);
    printf("Length org Printf: %d\n", len_org_printf);
    return 0;
}
