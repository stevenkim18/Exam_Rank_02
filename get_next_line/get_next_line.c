/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunkim <seunkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 12:18:27 by seunkim           #+#    #+#             */
/*   Updated: 2020/06/02 13:02:41 by seunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_strndup(char *s, int n)
{
	int	i;
	char	*ptr;

	i = 0;
	if (!(ptr = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (s[i] && i < n)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	s1_len;
	int	s2_len;
	char	*ptr;

	i = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (i - s1_len < s2_len)
	{
		ptr[i] = s2[i - s1_len];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	if ((char)c == 0)
		return (s + i);
	else
		return (NULL);
}

int	get_next_line(char **line)
{
	static char 	*data;
	char 		*buff;
	ssize_t		bytes;
	char		*tmp;
	char		*n_ptr;

	if (!(buff = (char*)malloc(sizeof(char) * 2)))
		return (-1);
	if (!data)
	{
		data = ft_strndup("", 0);
		while ((bytes = read(0, buff, 1) > 0))
		{
			buff[bytes] = '\0';
			tmp = data;
			data = ft_strjoin(data, buff);
			free(tmp);
		}
	}
	free(buff);
	n_ptr = ft_strchr(data, '\n');
	if (n_ptr)
	{
		*line = ft_strndup(data, n_ptr - data);
		data += n_ptr - data + 1;
		return (1);
	}
	else 
	{
		*line = ft_strndup(data, ft_strchr(data, '\0') - data);
		return (0);
	}
}		

int main(void)
{
	char 	*line;
	int	ret;

	line = NULL;
	while ((ret = get_next_line(&line)) > 0)
	{
		printf("%d %s\n", ret, line);
		free(line);
		line = NULL;
	}
	printf("%d %s\n", ret, line);
	free(line);
	while (1)
	{
	}
}
