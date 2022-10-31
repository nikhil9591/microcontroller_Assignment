#include<string.h>
int check(unsigned char* str)
{
    int i=0, length=0;
    int flag = 0;
    
    while(str[i]!='\0'){
			length++;
			i++;
		}
   
		i = 0;
    
    for(i=0;i < length ;i++){
        if(str[i] != str[length-i-1]){
            flag = 1;
            break;
           }
        }
    
    if (flag) {
        return flag;
    }    
    else {
        return flag;
    }
	
}