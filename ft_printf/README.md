# ft_printf
## 문제
### 허용 함수
malloc, free, write, va_start, va_arg, va_copy, va_end

### 문제 번역
* %s(문자열), %d(10진수), %x(16진수)
* width만 구현

## 처리 해야될 구간
* %s
~~~c
printf("10.0s |%10.0s\n", "Hello");
printf("10.s  |%10.s\n", "Hello");
printf("10s   |%10s\n", "Hello");
printf("10.4s |%10.4s\n", "HEllo");
printf("10.7s |%10.7s\n", "HEllo");
printf(".7s   |%.7s\n", "HEllo");
printf(".3s   |%.3s\n", "HEllo");
~~~

~~~
10.0s |          
10.s  |          
10s   |     Hello
10.4s |      HEll
10.7s |     HEllo
.7s   |HEllo$
.3s   |HEl$
~~~

* d
~~~c
printf("d    |%d\n", 1234);
printf("3d   |%3d\n", 1234);
printf("7d   |%7d\n", 1234);
printf(".d   |%.d\n", 1234);
printf(".3d  |%.3d\n", 1234);
printf(".6d  |%.6d\n", 1234);
printf(".6d  |%.6d\n", -1234);
printf("3.3d |%3.3d\n", 1234);
printf("3.3d |%3.3d\n", -1234);
printf("6.3d |%6.3d\n", 1234);
printf("6.3d |%6.3d\n", -1234);
printf("3.7d |%3.7d\n", 1234);
printf("3.7d |%3.7d\n", -1234);
printf("9.7d |%9.7d\n", 1234);
printf("9.7d |%9.7d\n", -1234);
~~~

~~~
d    |1234
3d   |1234
7d   |   1234
.d   |1234
.3d  |1234
.6d  |001234
.6d  |-001234
3.3d |1234
3.3d |-1234
6.3d |  1234
6.3d | -1234
3.7d |0001234
3.7d |-0001234
9.7d |  0001234
9.7d | -0001234
~~~

### 출력된 값 파일에 저장하기
~~~shell
./a.out >> result.txt
~~~

# 시험 대비
## 구조체
~~~c
typedef struct	s_struct
{
	char		*format;

	char		conversion;

	int		nprinted;

	int		width;
	int		dot;
	int		precision;
}			t_struct;
~~~
## 만들어야 할 기본 함수
* ft_strlen - 문자열 길이
* ft_numlen - 10진수 길이
* ft_hexlen - 16진수 길이 
* ft_putnstr - 문자열 n만큼 출력
* ft_putnbr - 10진수 출력
* ft_puthex - 16진수 출력
* ft_isdigit - 숫자인지 확인
* ft_isprint - 출력가능한 문자인지 확인
* ft_strchr - 문자열 중에서 문자를 찾으면 그 위치 리턴 없으면 널 리턴
* ft_strndup - n 만큼 문자열 할당

## 만들어야 할 커스텀 함수
### int ft_printf(const char *s, ...)
* 메인 함수
* va_list, va_start, va_end 사용

### int checkformat(const char *s, va_list ap)
* 문자열 s를 while문으로 돌면서 '%'를 찾으면 처리해 주는 함수

### char *findspecifier(const char *s)
* '%'를 찾았을때 그 뒤에 있는 서식자(s, d, x)까지를 찾아주는 함수

### void init(t_struct *f, char *format, char conversion)
* 구조체 초기화 해주는 함수

### void handlewidthandflag(t_struct *f, va_list ap)
* width, dot, flag 저장하는 함수

### void printstring(t_struct *f, va_list ap)
* 문자열 출력

### void pringnumber(t_struch *f, va_list ap)
* 10진수 16진수 

