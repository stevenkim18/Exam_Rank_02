#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include <stdio.h>

// 9. 진수 숫자 출력 함수
void	ft_putnbr_base(long long num, int base)
{
	char *dec = "0123456789";
	char *hex = "0123456789abcdef";

	if (num < 0)
		num = -num;
	if (num >= base)
	{
		ft_putnbr_base(num / base, base);
		ft_putnbr_base(num % base, base);
	}
	else
	{
		if (base == 10)
			write(1, &dec[num], 1);
		else if (base == 16)
			write(1, &hex[num], 1);
	}
}

// 8. 숫자 길이 함수
int	ft_numlen(int num)
{
	int	i;

	i = 1;
	while (num /= 10)
		i++;
	return (i);
}

int 	ft_hexlen(unsigned int num)
{
	int	i;
	
	i = 1;
	while (num /= 16)
		i++;
	return (i);
}

// 7. n 만큼 문자열 출력 함수
void	ft_putnstr(char *s, int n)
{
	int	i;

	i = 0;
	while (s[i] && i < n)
	{
		write(1, &s[i], 1);
		i++;
	}
}

// 6. 문자열 길이 함수
int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

// 5. width dot precision 처리하고 출력하는 함수
int	printwithflags(char *f, char conversion, va_list ap)
{
	int	width;
	int	dot;
	int	precision;
	int	nprinted;
	int	i;

	width = 0;
	dot = 0;
	precision = 0;
	nprinted = 0;
	i = 0;
	while (f[i])
	{
		if ((f[i] >= '0' && f[i] <= '9') && !dot)
			width = (width * 10) + (f[i] - 48);
		else if (f[i] == '.')
			dot = 1;
		else if ((f[i] >= '0' && f[i] <= '9') && dot)
			precision = (precision * 10) + (f[i] - 48);
		i++;
	}
	//printf("%d %d %d\n", width, dot, precision);
	
	char		*str;
	int		num;
	unsigned int 	unum;
	int		len;
	
	num = 0;
	unum = 0;
	len = 0;
	if (conversion == 's')
	{
		if (!(str = va_arg(ap, char *)))
			str = "(null)";
		len = ft_strlen(str);
		if (dot)
		{
			if (len < precision)
				precision = len;
		}
		else	// . 이 없으면 pre = 0이기 떄문에
			precision = len;
		i = 0;	// 공백 출력
		while (i < width - precision)
		{
			write(1, " ", 1);
			nprinted++;
			i++;
		}
		nprinted += precision;
		ft_putnstr(str, precision);
	}
	else if (conversion == 'd' || conversion == 'x')
	{
		if (conversion == 'd')
		{
			num = va_arg(ap, int);
			len = ft_numlen(num);
		}
		else if (conversion == 'x')
		{
			unum = va_arg(ap, unsigned int);
			len = ft_hexlen(unum);
		}
		if (num == 0 && unum == 0 && dot && precision == 0) // 예외처리
		{
			i = 0;
			while (i < width)
			{
				write(1, " ", 1);
				nprinted++;
				i++;
			}
			return (nprinted);
		}
		if (precision < len)
			precision = len;
		if (num < 0)	// 공백 처리
			precision++;
		i = 0;
		while (i < width - precision)
		{
			write(1, " ", 1);
			nprinted++;
			i++;
		}
		if (num < 0) // '-' 출력
		{
			write(1, "-", 1);
			len++;
		}
		i = 0;	    // 0 처리
		while (i < precision - len)
		{
			write(1, "0", 1);
			i++;
		}
		nprinted += precision;
		if (conversion == 'd')
			ft_putnbr_base(num, 10);
		else if (conversion == 'x')
			ft_putnbr_base(unum, 16);
	}
	free(f);
	return (nprinted);
}

// 4. n 길이 만큼 새로운 문자열 할당 함수
char	*ft_strndup(char *s, int n)
{
	int	i;
	char 	*ptr;

	if (!(ptr = (char *)malloc(sizeof(char *) * (n + 1))))
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// 3. 서식자의 위치를 찾아주는 함수
char	*findsdx(char *s)
{
	int	i;
	
	i = 0;
	while (s[i] && ((s[i] >= '0' && s[i] <= '9') || s[i] == '.'))
		i++;
	if (s[i] >= 32 && s[i] <= 126)
	{
		//printf("s[i] = %c\n", s[i]);
		if (s[i] == 's' || s[i] == 'd' || s[i] == 'x')
			return (s + i);
		else
			return (NULL);
	}
	return (NULL);
}	

// 2. %를 찾아서 처리해주는 함수
int	checkformat(va_list ap, char *s)
{
	int	i;
	char	*conversion;
	int	ret;
	char	*format;
	
	ret = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			conversion = findsdx(s + i + 1);
			//printf("con = %c\n", *conversion);
			if (conversion)
			{	// fstrndup s + i 하는 것이 포인트!
				format = ft_strndup(s + i, (conversion + 1) - (s + i));
				//printf("format = %s\n", format);
				ret += printwithflags(format, *conversion, ap);
				i += ((conversion) - (s + i));
			}
			else	// sdx가 없을 때 한 칸 앞으로
				i++;
		}
		else // % 없는 문자는 그냥 출력
		{
			write(1, &s[i], 1);
			ret++;
		}
		i++;
	}
	return (ret);
}

// 1. 프로토 타입 함수
int	ft_printf(const char *s, ...)
{
	int	ret;
	va_list	ap;

	if (!s)
		return (-1);
	va_start(ap, s);
	// 상수 타입을 일반 타입으로 변환 중요!!
	ret = checkformat(ap, (char *)s);
	va_end(ap);
	return (ret);
}

