# ft_printf
## 문제
### 허용 함수
malloc, free, write, va_start, va_arg, va_copy, va_end

### 문제 번역
* %s(문자열), %d(10진수), %x(16진수)
* width만 구현

## 처리 해야될 구간
~~~c
printf(".7d   |%.7d\n", -12345);
printf("10d   |%10d\n", -12345);
printf("10.4d |%10.4d\n", 12345);
printf("10.7d |%10.7d\n", 12345);

printf("10.0s |%10.0s\n", "Hello");
printf("10.s  |%10.s\n", "Hello");
printf("10s   |%10s\n", "Hello");
printf("10.4s |%10.4s\n", "HEllo");
printf("10.7s |%10.7s\n", "HEllo");
~~~

~~~
.7d   |-0012345
10d   |    -12345
10.4d |     12345
10.7d |   0012345
10.0s |          
10.s  |          
10s   |     Hello
10.4s |      HEll
10.7s |     HEllo
~~~
