/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 18:49:46 by lemarque          #+#    #+#             */
/*   Updated: 2022/01/13 13:36:31 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static int	set_c(char const **s, char *c, int count)
{
	while (**s && (**s == *c || **s == '\''))
	{
		if (**s == '\'')
		{
			*c = '\'';
			count++;
		}
		(*s)++;
	}
	if (count == 2)
	{
		count = 0;
		*c = ' ';
	}
	return (count);
}

static int	get_words_number(char const *str, char c)
{
	int		d;
	int		count;

	count = 0;
	d = 0;
	while (*str)
	{
		count = set_c(&str, &c, count);
		if (*str && (*str != c && *str != '\''))
			d++;
		while (*str && (*str != c && *str != '\''))
			str++;
	}
	return (d);
}

static int	get_word_size(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (*str && (*str != c && *str != '\''))
	{
		i++;
		str++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**arr_words;
	size_t	word_size;
	size_t	i;
	int		count;
	size_t	words_count;

	words_count = get_words_number(s,c);
	count = 0;
	i = 0;
	arr_words = malloc(sizeof(char *) * (words_count + 1));
	if (!arr_words)
		return (NULL);
	while (*s)
	{
		count = set_c(&s, &c, count);
		word_size = get_word_size(s, c);
		if (*s != c && *s != '\'' && i < words_count)
		{
			arr_words[i] = ft_substr(s, 0, word_size);
			if (!arr_words[i])
				return (NULL);
			s += word_size;
			i++;
		}
	}
	arr_words[i] = NULL;
	return (arr_words);
}
