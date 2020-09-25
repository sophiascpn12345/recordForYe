#include <sys/types.h>
#include <regex.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc != 3){
	   printf("Usage: %s RegexString And Text\n", argv[0]);
	   return 1;
	}
	const char * p_regex_str = argv[1];
	const char * p_txt = argv[2];
	regex_t oregex;   //编译后的结构体
	int ret = 0;
	char emsg[1024] = {0};  //保持错误信息的数组
	size_t emsg_len = 0;

	if((ret = regcomp(&oregex, p_regex_str, REG_EXTENDED|REG_NOSUB)) == 0) { //编译正则表达式，扩展正则
			if((ret = regexec(&oregex, p_txt, 0 ,NULL, 0)) == 0) { //执行匹配，不保存匹配的返回值
					printf("%s matches %s\n",p_txt,p_regex_str);
					regfree(&oregex);
					return 0;
			}
	}
	emsg_len = regerror(ret, &oregex, emsg, sizeof(emsg));   //正则编译错误，存emsg中错误描述
	emsg_len = emsg_len < sizeof(emsg) ? emsg_len : sizeof(emsg) -1; //错误信息较长特殊情况

	emsg[emsg_len] = '\0';
	printf("Regex error Msg: %s\n", emsg);

	regfree(&oregex);

	return 1;   //非正常退出
}


'''
 ./regex "([0-9]{1,3}\.){3}[0-9]{1,3}" "129.115.235.123"

 ./regex "http:\/\/www\..*\.com" "http://www.sina.com"
'''
