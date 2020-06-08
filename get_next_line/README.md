# get_next_line
## 문제
### 허용 함수
read, free, malloc

### 제출 파일
get_next_line.c, get_next_line.h

### 문제 번역
* file descriptor 0(표준 입력 - stdin)에서 한 줄을 읽어와서 "line"에 저장하는 함수를 만들어라
* int get_next_line(char **line);
* 이 함수는 메모리 누수가 없어야 한다.
* "라인을 읽어왔다"의 의미는 개행('\n')으로 끝나거나 파일의 끝(EOF)으로 끝나는 0에서 n개의 문자들을 읽어 왔다는 이야기이다.
* line 에 저장될 값은 '\n'은 포함 되지 않는다.
* line은 읽어온 한 줄을 저장할 곳 포인터의 주소이다.
* 한줄을 읽어왔으면 리턴 1, 파일의 마지막 줄을 읽었으면 리턴 0, 애러가 발생했으면 리턴 -1.
* 파일에 끝에 도달했을 때 현재 버퍼에 있는 값들을 line에 저장하고 만약 버퍼가 비어 있다면 빈 문자열을 line에 저장해야 한다.
* 파일에 끝네 도달했을 때 마지막 버퍼를 제외하고는 모든 메모리는 해제되어야 한다.
* line도 해제 가능한 변수여야 한다.
* get_next_line은 반복문에서 작동하고 한줄의 길이가 얼마든 간에 fd 안에 있는 텍스트가 끝날때까지 반복문을 돌면서 한줄씩 읽어 온다.
* 우리가 만든 함수는 표준 출력, 파일에서도 잘 읽어와야 한다.

## 메모리 누수 체크하기!
* main 함수 마지막에 무한 루프 넣기
~~~c
while (1)
{
}
~~~

* 컴파일 하고 실행
~~~shell
./a.out
~~~

* 다른 터미널을 열고 ps 명령어 사용해서 pid 값 찾기
~~~shell
$ps
~~~
~~~
PID TTY           TIME CMD
  468 ttys004    0:00.04 /Applications/iTerm.app/Contents/MacOS/iTerm2 --server login -fp stevenkim
  470 ttys004    0:00.58 -zsh
  812 ttys005    0:00.51 /bin/zsh -l
 5351 ttys005    0:03.03 ./a.out
~~~

* pid 값 넣어서 테스트
~~~shell
while 1; do leaks 5351; sleep 3; clear; done
~~~

~~~
~/Desktop/42/Exam_Rank_02/get_next_line
Process:         a.out [5351]
Path:            /Users/USER/Desktop/*/a.out
Load Address:    0x10a757000
Identifier:      a.out
Version:         ???
Code Type:       X86-64
Parent Process:  zsh [812]

Date/Time:       2020-06-01 23:37:29.540 +0900
Launch Time:     2020-06-01 23:35:03.883 +0900
OS Version:      Mac OS X 10.15.4 (19E266)
Report Version:  7
Analysis Tool:   /usr/bin/leaks

Physical footprint:         300K
Physical footprint (peak):  300K
----

leaks Report Version: 4.0
Process 5351: 154 nodes malloced for 12 KB
Process 5351: 0 leaks for 0 total leaked bytes
~~~


## 문제 풀이 순서
1. get_next_line.h 파일 만들기
2. 함수 만들기
    - ft_strlen
    - ft_strjoin
    - ft_strchr
    - ft_strudup
3. 입력한 데이터를 static 변수에 저장되었는지 확인하기
4. main 함수를 만들어서 제대로 함수가 동작하는지 확인.
