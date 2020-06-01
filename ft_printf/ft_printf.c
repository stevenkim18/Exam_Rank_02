/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunkim <seunkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 17:13:35 by seunkim           #+#    #+#             */
/*   Updated: 2020/05/27 17:18:58 by seunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

typedef struct	s_struct
{
	char		*format;

	char		conversion;

	int			nprinted;

	int			minus;
	int			zero;

	int			width;
	int			dot;
	int			precision;
}				t_struct;

// 문자열 길이
int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// 숫자 길이
int		ft_numlen(int num)
{
	int		i;

	i = 1;
	while (num /= 10)
		i++;
	return (i);
}

// 16진수 길이
int		ft_hexlen(unsigned int num)
{
	int		i;

	i = 1;
	while (num /= 16)
		i++;
	return (i);
}

// 문자열 출력
void	ft_putnstr(char *s, int n)
{
	int		i;

	i = 0;
	while (s[i] && i < n)
	{	
		write(1, &s[i], 1);
		i++;
	}
}

// 10진수 출력
void	ft_putnbr(long long num)
{
	int		i;

	i = 0;
	if (num < 0)
		num = -num;
	if (num >= 10)
	{
		ft_putnbr(num / 10);
		ft_putnbr(num % 10);
	}
	else
	{
		num += 48;
		write(1, &num, 1);
	}
}

// 16진수 출력
void	ft_puthex(long long num)
{
	char *hex;

	hex = "0123456789abcdef";
	if (num < 0)
		num = -num;
	if (num >= 16)
	{
		ft_puthex(num / 16);
		ft_puthex(num % 16);
	}
	else 
		write(1, &hex[num], 1);
}

// n만큼 까지 문자열 할당 함수
char	*ft_strndup(char const *s, int n)
{
	int 	i;
	char	*ptr;

	i = 0;
	if (!(ptr = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr); 
}

// 서식자를 찾아서 리턴하는 함수
char	*findspecifier(const char *s)
{
	int		i;
	char	*conversion;

	i = 0;
	// 숫자랑 '.' 만 포함.
	while (s[i] && (isdigit(s[i]) || s[i] == '.'))
		i++;
	if (isprint(s[i]))
	{
		conversion = strchr("sdx", s[i]);
		if (conversion)
			return ((char*)s + i);
		else
			return (NULL);
	}
	return (NULL);
}

// 구조체 초기화
void	init(t_struct *f, char *format, char conversion)
{
	f->format = format;
	f->conversion = conversion;
	f->nprinted = 0;
	f->minus = 0;
	f->zero = 0;
	f->width = 0;
	f->dot = 0;
	f->precision = 0;
}

// width '.' presicion 처리하기
void	handlewidthandflag(t_struct *f, va_list ap)
{
	int		i;

	i = 0;
	while (f->format[i])
	{
		// witdh
		if (isdigit(f->format[i]) && !(f->dot))
			f->width = (f->width) * 10 + (f->format[i] - 48);
		// flag ','
		else if (f->format[i] == '.' && !(f->dot))
			f->dot = 1;
		// presicion
		else if (isdigit(f->format[i]) && (f->dot))
			f->precision = (f->precision) * 10 + (f->format[i] - 48);
		i++;
	}
	// 문자열 
	if (f->conversion == 's')
	{
		char 	*str;
		int		len;
		int		i;

		// 문자열에 null 일떄 처리
		if (!(str = va_arg(ap, char *)))
			str = "(null)";
		len = ft_strlen(str);
		// presicion 처리
		if (f->dot)
		{
			if (len < f->precision)
				f->precision = len;
		}
		// presicion이 없을 때
		else
			f->precision = len;
		i = 0;
		// 공백 출력
		if (f->width > f->precision)
		{	
			while (i < (f->width - f->precision))
			{
				write(1, " ", 1);
				f->nprinted += 1;
				i++;
			}
		}
		ft_putnstr(str, f->precision);
		f->nprinted += f->precision;
	}
	// 10진수
	else if (f->conversion == 'd' || f->conversion == 'x')
	{
		int 			num;
		unsigned int 	unum;
		int 			len;
		int 			i;

		num = 0;
		unum = 0;
		if (f->conversion == 'd')
		{
			num = va_arg(ap, int);
			len = ft_numlen(num);
		}
		else if (f->conversion == 'x')
		{
			unum = va_arg(ap, unsigned int);
			len = ft_hexlen(unum);
		}
		// %.d, 0 / %4.0d, 0 처리
		if (((unum == 0 && num == 0) && f->dot && f->precision == 0))
		{
			i = 0;
			while (i < f->width)
			{
				write(1, " ", 1);
				f->nprinted++;
				i++;
			}
			return ;
		}
		if (f->precision < len)
			f->precision = len;
		i = 0;
		if (num < 0)
			f->precision++;
		// 공백
		while (i < f->width - f->precision)
		{
			write(1, " ", 1);
			f->nprinted++;
			i++;
		}
		// 음수 '-' 처리
		if (num < 0)
		{
			write(1, "-", 1);
			len++;
		}
		// precision에 따라 0 출력
		i = 0;
		while (i < f->precision - len)
		{
			write(1, "0", 1);
			i++;
		}
		if (f->conversion == 'd')
			ft_putnbr(num);
		else if (f->conversion == 'x')
			ft_puthex(unum);
		f->nprinted += f->precision;
	}
}

// 서식자를 확인해서 처리해 주는 함수
int		checkformat(const char *s, va_list ap)
{
	int			i;
	int 		ret;
	t_struct	*f;
	char		*tmp;

	ret = 0;
	if (!(f = (t_struct*)malloc(sizeof(t_struct))))
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			// % 다음 부터 찾기
			tmp = findspecifier(s + i + 1);
			if (tmp)
			{
				init(f, ft_strndup(s + i, (tmp + 1) - (s + i)), *tmp);
				handlewidthandflag(f, ap);
				i = i + ((tmp) - (s + i));
				ret += f->nprinted;
			}
			else
				i++;
		}
		// %가 아닐때는 기본 출력 기능만 함.
		else 
		{
				ret += 1;
				write(1, &s[i], 1);
		} 
		i++;
	}
	return (ret);
}

// 프로토타입 함수
int		ft_printf(const char *s, ...)
{
	va_list ap;
	int 	ret;

	if (!s)
		return (0);
	va_start(ap, s);
	ret = checkformat(s, ap);
	va_end(ap);
	return (ret);
}
