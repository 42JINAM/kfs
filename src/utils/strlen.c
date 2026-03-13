#include <stddef.h>

size_t	strlen(const char	*str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
