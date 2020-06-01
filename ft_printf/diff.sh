gcc -Wall -Wextra -Werror ori.c -o ori.out
gcc -Wall -Wextra -Werror cus.c ft_printf.c -o cus.out

chmod 775 ./ori.out ./cus.out

./ori.out >> ori.txt
./cus.out >> cus.txt

diff -d ori.txt cus.txt
