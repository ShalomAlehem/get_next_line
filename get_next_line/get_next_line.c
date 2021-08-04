#include "get_next_line.h"

int	ft_n_pt(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	if (str[i] == '\n')
		return (i);
	return (-1);
}

char	*ft_get_line(char **remainer)
{
	char	*new_line;
	char	*temp;

	new_line = ft_calloc(1, 1);
	if (*remainer && ft_strlen(*remainer) > 0)
	{
		if (ft_n_pt(*remainer) == -1)
		{
			ft_freemem(&new_line);
			new_line = ft_strdup(*remainer);
			ft_freemem(remainer);
		}
		else
		{
			new_line = ft_strjoin(new_line, *remainer, ft_n_pt(*remainer) + 1);
			temp = *remainer;
			*remainer = ft_strdup(ft_strchr(*remainer, '\n') + 1);
			ft_freemem(&temp);
		}
	}
	return (new_line);
}

void	ft_freemem(char **to_free)
{
	if (!*to_free)
		return ;
	free(*to_free);
	*to_free = NULL;
}

void	ft_liner(int fd, char *buff, char **line, char **remainer)
{
	int	bwr;

	bwr = 1;
	while (bwr && (!remainer || ft_n_pt(*line) == -1))
	{
		bwr = read(fd, buff, BUFFER_SIZE);
		buff[bwr] = '\0';
		if (!(ft_strchr(buff, '\n')) && bwr == BUFFER_SIZE)
			*line = ft_strjoin(*line, buff, ft_strlen(buff));
		else if (!ft_strchr(buff, '\n') && bwr < BUFFER_SIZE)
		{
			*line = ft_strjoin(*line, buff, ft_strlen(buff));
			break ;
		}
		else if (ft_strlen(buff) > 0)
		{
			*line = ft_strjoin(*line, buff, (ft_n_pt(buff) + 1));
			*remainer = ft_strdup(ft_strchr(buff, '\n') + 1);
			break ;
		}
	}
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*remainer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = ft_get_line(&remainer);
	ft_liner(fd, buffer, &line, &remainer);
	if (remainer && *remainer == '\0')
		ft_freemem(&remainer);
	if (!ft_strlen(remainer) && !ft_strlen(line))
	{
		ft_freemem(&line);
		return (NULL);
	}
	return (line);
}

int main(void)
{
	int fd;
	char *str;

	fd = open("text1.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
	printf("%s", str);
	str = get_next_line(fd);
	}
	printf("%s", str);
	printf("%s", str);
	return (0);
}
