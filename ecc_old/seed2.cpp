#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define str_length 16
#define password_length 32

char password[password_length + 1];

void seed(void){
    /*
    * �ϐ��錾
    */
    char str[str_length + 1];
    
    int i, j, k, rnd;
    char confirm[2];
    
    /*
    * �����̏�����
    */
    srand(clock());
  i=0;
  while(i<1000)
    i++;
    /*
    * ���������ƃp�X���[�h�̐���
    */
    for(i = 0; i < str_length; i++) {
        for(j = 0; j < 2; j++) {
            k = i * 2 + j;
            do {
                rnd = rand();
                password[k] = str[i] + rnd;
            }while(!isalnum(password[k]));
        }
    }
    
    /*
    * NULL�����̑}��
    */
    password[password_length] = '\0';
    
    /*
    * �p�X���[�h�̏o��
    */
//    printf("�����p�X���[�h�F%s",password);
    
//return;
  
}


