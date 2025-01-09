#include "philo.h"

static int		isnumber(char *nbr)
{
	int		i;

	i = 0;
	while (nbr[i])
	{
		if (!(nbr[i] >= 48 && nbr[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_args(int argc, char **argv)
{
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		if (!is_number(argc[i]))
			return (1);
		i++;
	}
	return (0);
}
