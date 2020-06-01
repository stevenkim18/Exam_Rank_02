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
