#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cstdlib>
using namespace std;
//cracking 1.1 Implement an algorithm to determine if a string has all unique characters
bool is_all_unique_char(char *str)
{
   bool hash[256];
   memset(hash, 0, sizeof(bool)*256);
   for (;*str != '\0'; str++) {
       if (hash[*str]) {
           return false;
       }            
       hash[*str] = true;
   }
   return true;
}
bool is_all_unique_char_v2(char *str)
{
    char hash[32];
    int index, bit;
    memset(hash, 0, 32);
    for (; *str != '\0'; str++) {
        index = (*str) / 8;
        bit = (*str) % 8;
        if (hash[index] & (1 << bit)) {
            return false;
        }
        hash[index] = hash[index] | (1 << bit);
    }

    return true;
}
//cracking 1.2 Implement a function to reverse a null-terminated string
void reverse_string(char *str)
{
    assert(str && *str != '\0');
    char *start = str;
    int len = strlen(str);
    char *end = str + len - 1;

    while (start != end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    
}
//cracking1.3 Given two strings, write a method to decide if one is permutation of the other
bool is_anagram(char *s1, char *s2) {
    int hash[256];
    memset(hash, 0, sizeof(int)*256);

    for (; *s1; s1++) {
        hash[*s1]++;
    }
    for (; *s2; s2++) {
        hash[*s2]--;
    }

    int i;
    for (i = 0; i < 256; i++){
        if (hash[i])
            return false;
    }

    return true;
}
//cracking1.4 write a method to replace all spaces in a string with '%20'
void replace_space(char *str, int len)
{
    char *temp = str;
    int space_num = 0;
    int old_len = strlen(str);
    while (*temp != '\0'){
        if (*temp++ == ' ')
            space_num++;
    }
    int new_len = old_len + space_num * 2; 
    if (new_len > len-1) {
        printf("Have not enough space to replace\n");
        exit(1);
    }
    int i;
    int j = new_len;
    *(str+j--) = '\0';
    for(i = old_len-1; i >= 0; i--) {
        if (*(str+i) == ' ') {
            *(str+j--) = '0';
            *(str+j--) = '2';
            *(str+j--) = '%';
        } else {
            *(str+j--) = *(str+i);
        }
    }

}
/* cracking1.5
 * Implement a method to perform basic string compression using the counts of repeated characters. For example, the string aabcccccaaa would become a2blc5a3.
 * If the "compressed" string would not become smaller than the original string,your method should return the original string.
 */
void itoa(char *str, int num)
{
    int i = 0, flag = 0;
    if (num < 0) {
        num = -num;
        flag = 1;
    }
    while (num) {
        str[i++] = num % 10 + '0';
        num /= 10;
    }
    if (flag) {
        str[i++] = '-';
    }
    str[i] = '\0';
    reverse_string(str);

}
char *compress_string(char *str)
{
    int len = strlen(str);
    int compressed_len = 0;
    char *compressed_str = (char *)malloc(sizeof(2*len)); 
    char num_str[10];
    char *tmp = str;
    
    char last_char = *tmp;
    int count = 1;
    int i;
    for (tmp = tmp +1; *tmp; tmp++) {
        if (*tmp == last_char) {
            count++;
        } else {
            *(compressed_str+compressed_len++) = last_char;
            itoa(num_str, count);
            strncpy(compressed_str+compressed_len, num_str, strlen(num_str));
            compressed_len += strlen(num_str);
            last_char = *tmp;    
            count = 1;
        }
        
    }
    
    *(compressed_str+compressed_len++) = last_char;
    itoa(num_str, count);
    strncpy(compressed_str+compressed_len, num_str, strlen(num_str));
    compressed_len += strlen(num_str);
    compressed_str[compressed_len] = '\0';
    printf("len=%d, com_len=%d\n", len, compressed_len);
    return (len > compressed_len) ? compressed_str : str;
}
char *read_string()
{
    char *s = (char *)malloc(256);
    fgets(s, 255, stdin);
    s[strlen(s)-1] = '\0';
    return s;
}
int main() 
{
   /* 1.1
    char str[100];
    fgets(str, 99, stdin);
    if (!is_all_unique_char_v2(str)) {
        printf("%s is not unique\n", str);
    } else {
        printf("%s is unique\n", str);
    }
    */

    /*1.2
    char str[] ="hello world";
    reserve_string(str);
    printf("After reverse %s\n",str);
    */
    /*1.3
    char *s1 = read_string();
    char *s2 = read_string();

    if (is_anagram(s1, s2)) {
        printf("%s and %s is anagram\n", s1, s2);
    } else {
        printf("%s and %s is not anagram\n", s1, s2);

    }
    free(s1);
    free(s2);
    */
    /*1.4
    char *s = read_string();
    replace_space(s,256);
    printf("After replace is %s\n", s);
    */
    /*1.5    
    char str[] = "aabbbbbccdddddefghi";
    printf("after compress is %s\n", compress_string(str));
    */
    return 0;
}

