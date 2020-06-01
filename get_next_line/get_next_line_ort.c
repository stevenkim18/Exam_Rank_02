/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunkim <seunkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/27 12:54:27 by seunkim           #+#    #+#             */
/*   Updated: 2020/05/27 16:23:57 by seunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

char		*ft_strchr(char *s, int c)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
	{
		if (s[idx] == (char)c)
			return (s + idx);
		idx++;
	}
	if (!(char)c)
		return (s + idx);
	else
		return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;
	size_t	idx;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(ptr = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	idx = 0;
	while (s1[idx] && idx < s1_len)
	{
		ptr[idx] = s1[idx];
		idx++;
	}
	while (s2[idx - s1_len] && idx - s1_len < s2_len)
	{
		ptr[idx] = s2[idx - ft_strlen(s1)];
		idx++;
	}
	ptr[idx] = '\0';
	return (ptr);
}

char		*ft_strndup(char const *s, int n)
{
	int		idx;
	char	*ptr;

	idx = 0;
	if (!(ptr = (char*)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	while (idx < n)
	{
		ptr[idx] = s[idx];
		idx++;
	}
	ptr[idx] = '\0';
	return (ptr);
}

int		check_error(char **buff, int fd)
{
	if (!(*buff = (char*)malloc(sizeof(char) * (128 + 1))))
		return (0);
	if (fd <= -1 || fd >= 6)
		return (0);
	return (1);
}

int		getlinestr(char **line, char **data, char **first_data)
{
	if (ft_strchr(*data, '\n'))
	{
		*line = ft_strndup(*data, ft_strchr(*data, '\n') - *data);
		*data = ft_strchr(*data, '\n') + 1;
		return (1);
	}
	else
	{
		*line = ft_strndup(*data, ft_strchr(*data, '\0') - *data);
		free(*first_data);
		*data = NULL;
		return (0);
	}
}

int		get_next_line(char **line)
{
	int		fd;
	char		*buff;
	static char	*data[8192];
	char		*tmp;
	ssize_t		bytes;

	fd = 0;
	if (line == NULL)
		return (-1);
	if (!(check_error(&buff, fd)))
		return (-1);
	if (!data[fd])
	{
		data[fd] = ft_strndup("", 0);
		while ((bytes = read(fd, buff, 128)) > 0)
		{
			buff[bytes] = '\0';
			tmp = data[fd];
			data[fd] = ft_strjoin(data[fd], buff);
			free(tmp);
		}
		data[4096 + fd] = data[fd];
	}
	free(buff);
	return (getlinestr(&*line, &data[fd], &data[4096 + fd]));
}
