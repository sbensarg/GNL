/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbensarg <sbensarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:34:48 by sbensarg          #+#    #+#             */
/*   Updated: 2019/11/07 16:21:15 by sbensarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


size_t		ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*psrc;
	char	*pdest;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	psrc = (char*)src;
	pdest = (char*)dest;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		lens1;
	int		lens2;
	int		sum;
	char	*newstr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen((char *)s1);
	lens2 = ft_strlen((char *)s2);
	sum = lens1 + lens2;
	newstr = (char *)malloc(sum + 1);
	if (newstr == NULL)
		return (NULL);
	ft_memcpy(newstr, s1, lens1);
	ft_memcpy(newstr + lens1, s2, lens2 + 1);
	return (newstr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != c && *s != '\0')
	{
		s++;
	}
	if (*s == c)
	{
		return ((char*)s);
	}
	else
	{
		return (NULL);
	}
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *ptr;

	ptr = b;
	while ((int)len > 0)
	{
		*ptr = c;
		ptr++;
		len--;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_bytes;
	void	*ptr;

	total_bytes = count * size;
	ptr = malloc(total_bytes);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_bytes);
	return (ptr);
}

char *verif_reste(char *rest, char **line)
{
	char *s = NULL;
	int slen;

	slen = ft_strlen(rest);
	if(rest)
	{
		if((s = ft_strchr(rest, '\n')))
		{
			*s = '\0';
			*line = ft_strdup(rest);
			ft_memcpy(rest, s++, slen);
		}
		else
		{
			*line = ft_strdup(rest);
			bzero(rest, slen);
		}
	}
	else
		*line = ft_calloc(1, 1);
	return (s);
}


int get_next_line(int fd, char **line)
{
	char buf[BUFFER_SIZE + 1];
	char *s;
	static char *rest;
	int ret;

	s = verif_reste(rest, line);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = '\0';
		if ((s = ft_strchr(buf, '\n')))
		{
			*s = '\0';
			rest = ft_strdup(s++);
			break;
		}
	*line = ft_strjoin(*line, buf);
	}
	return (0);
}

int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);

	get_next_line(fd, &line);
	printf("%s\n", line);

	get_next_line(fd, &line);
	printf("%s\n", line);

	get_next_line(fd, &line);
	printf("%s\n", line);
}
