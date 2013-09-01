#include <iostream>
#include <stack>
#include <vector>
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
/* cracking 1.8
 * Assume you have a method isSubstring which checks if one word isa substring of another.
 * Given two strings,s1 and s2,write code to check If s2 is a rotation of s1 
 * using only one call to isSubstring (e.g.,"waterbottLe"is a rotation of "erbottlewat").
 */
char *is_substring(char *source, char *substr)
{
    assert(source && substr);
    char *p, *q, *r;
    for (p = source; *p; p++) {
        q = p;
        r = substr;
        while (*r && *r++ == *q++) ;
        if (*r == '\0')
            return p;
    }
    return NULL;
}

bool is_rotation(char *s1, char *s2)
{
    assert(s1 && s2);
    int len = strlen(s1);
    char *news1 = (char*)malloc(len*2+1);
    int i;
    for (i = 0; i < len; i++) {
        news1[i] = news1[i+len] = s1[i];
    }
    news1[2*len] = '\0';

    if (is_substring(news1, s2)) {
        return true;
    } else {
        return false;
    }
}
/*
 * 剑指offer 28
 *给定一个字符串，打印出这个字符串中字符的所有排列
 */
void print_string_permutation(char *str, char *start)
{
    assert(str);
    if (*start == '\0') {
        printf("%s\n", str);
        return ;
    }

    char temp, *p;
    for (p = start; *p; p++) {
        temp = *start;
        *start = *p;
        *p = temp;

        print_string_permutation(str,start+1);

        temp = *start;
        *start = *p;
        *p = temp;
    }
}
/*
 * 剑指offer 28 扩展
 * 给定一个字符串，打印出这个字符串中字符的所有组合
 * abc->a,b,c,ab,ac,bc,abc
 */
void print_string_combination(char *s, int left, vector<char> &st)
{
    if (left == 0) {
        vector<char>::iterator iter;
        for (iter = st.begin(); iter != st.end(); iter++) {
            printf("%c", *iter);
        }
        printf("\n");
        return ;
    }
    if (*s == '\0') {
        return ;
    }
    char *p;
    for (p = s; *p; p++) {
        st.push_back(*p);
        print_string_combination(p+1, left-1,st);
        st.pop_back();
    }
}
void string_combination(char *str)
{
    assert(str && *str != '\0');
    int i;
    vector<char> st;
    for (i = 1; i <= strlen(str); i++)
        print_string_combination(str, i, st);
}
/*
 * 剑指offer 42
 * 给定一个英文句子，反转句子中单词的顺序，但单词中字符的顺序不变 
 * 如I am a student. 反转后为student. a am I
 */
void reverse_string_v2(char *begin, char *end)
{
    assert(begin && end);
    while (begin < end) {
        char temp = *begin;
        *begin++ = *end;
        *end-- = temp;
    }
}
char *reverse_sentence(char *sentence)
{
    reverse_string_v2(sentence, sentence+strlen(sentence)-1);

    char *begin, *end;
    begin = end = sentence;

    while (*begin != '\0') {
        if (*begin == ' ') {
            begin++;
            end++;
        } else if (*end == ' ' || *end == '\0') {
            reverse_string_v2(begin, end-1);
            begin = end;
        } else {
            end++;
        }
    }

    return sentence;

}
/*
 * 剑指offer 42 扩展
 * 字符串的左旋转就是把字符串前面的若干个字符移到字符串的尾部，实现字符串左旋功能 
 * 如abcdefg旋转位置为2，则旋转后为cdefgab
 */
char * left_rotate_string(char *str, int pos)
{
    assert(str);
    int len = strlen(str);
    if (pos > 0 && pos < len) {
        reverse_string_v2(str, str+pos-1);
        reverse_string_v2(str+pos, str+len-1);
        reverse_string_v2(str, str+len-1);
    }

    return str;
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
   /*1.8 
    char s1[] = "hello world";
    char s2[] = "worldhelo ";
    if (is_rotation(s1, s2)) {
        printf ("%s is rotation of %s\n", s2, s1);
    }else {
        printf ("%s is not rotation of %s\n", s2, s1);

    }
    */
    /* offer 28
    char str[] = "abc";
    print_string_permutation(str, str);
    */
    /* offer 28 extend
    char str[] = "abc";
    string_combination(str);
    */
    /* offer 42
    char sen[] = "hello! I am a student!";
    printf("%s after reverse_sencence is %s",sen, reverse_sentence(sen));
    */
    char str[] = "abcdefg";
    printf("%s after left rotate 2 is %s\n", str, left_rotate_string(str, 2));
    return 0;
}

