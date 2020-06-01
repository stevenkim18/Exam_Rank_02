/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunkim <seunkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:37:44 by seunkim           #+#    #+#             */
/*   Updated: 2020/06/01 19:37:45 by seunkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int     s1_len;
	int     s2_len;
	int     i;

	s1_len = strlen(s1);
	s2_len = strlen(s2);
	if (!(ptr = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	i = 0;
	while (s1[i] && i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[i - s1_len] && i - s1_len < s2_len)
	{
		ptr[i] = s2[i - s1_len];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char    *ft_strndup(char *s, int n)
{
    int     i;
    char    *str;

    if (!(str = (char*)malloc(sizeof(char) * (n + 1))))
        return (NULL);
    i = 0;
    while (i < n)
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

int     get_next_line(char **line)
{
    static char *data;
    char        *buff;
    char        *tmp;
    ssize_t     bytes;
    int         fd;

    // 버퍼사이즈 1
    fd = open("text.txt", O_RDONLY);
    if (!(buff = (char*)malloc(sizeof(char) * 2)))
        return (-1);
    if (!data)
    {
        data = strdup("");
        while ((bytes = read(fd, buff, 1)) > 0)
        {
            buff[bytes] = '\0';
            tmp = data;
            data = ft_strjoin(data, buff);
            free(tmp);
        }
        //printf("data = %s\n", data);
    }
    free(buff);
    if (strchr(data, '\n'))
    { 
        *line = ft_strndup(data, strchr(data, '\n') - data);
        data = strchr(data, '\n') + 1;
        return (1);
    }
    else 
    {
        *line = ft_strndup(data, strchr(data, '\0') - data);
        //free(data);
        return (0);
    }
}

int main(void)
{
    char    *line;
    int     ret;

    line = NULL;
    while ((ret = get_next_line(&line)) > 0)
    {
        printf("%d : %s\n", ret, line);
        free(line);
        line = NULL;
    }
    printf("%d : %s\n", ret, line);
    //free(line);
    line = NULL;
}
