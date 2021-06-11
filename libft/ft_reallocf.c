
#include "libft.h"

void	*ft_reallocf(void *old_alloc, size_t old_size, size_t new_size)
{
	unsigned char	*old_alloc_t;
	unsigned char	*new_alloc;
	size_t			i;

	i = 0;
	if (old_alloc == NULL)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(old_alloc);
		return (NULL);
	}
	old_alloc_t = (unsigned char *)old_alloc;
	if ((new_alloc = (unsigned char *)malloc(new_size)) == NULL)
	{
		free(old_alloc);
		return (NULL);
	}
	while (i < old_size && i < new_size)
	{
		new_alloc[i] = old_alloc_t[i];
		i++;
	}
	free(old_alloc);
	return (new_alloc);
}