#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	ft_liner(int fd, char *buff, char **line, char **remainer);
void	ft_freemem(char **to_free);
char	*ft_get_line(char **remainer);
int		ft_n_pt(char *str);
size_t	ft_strlen(const char *str);
char	*ft_strchr (char *str, int c);
char	*ft_strdup (const char *s1);
void	ft_freemem(char **to_free);
char	*ft_strcpy(char *dst, char *src);
char	*ft_strjoin(char *s1, char *s2, int len);
void	*ft_calloc(size_t count, size_t n);

#endif
