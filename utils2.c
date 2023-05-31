#include "minishell.h"

// env de istediğin bölümün adını yazıyorsun sadece, "PATH" gibi. Sana o arrayin adresini döndürüyor
char	*find_in_env(char *find)
{
	int		i;
	int		j;
	int		index;

	i = 0;
	while (g_var.env_size > i)
	{
		j = 0;
		index = 0;
		while (g_var.env[i][j] && (find[index] == g_var.env[i][j]))
		{
			j++;
			index++;
			if (index == ft_strlen(find) && g_var.env[i][j] == '=')
				return (g_var.env[i]);
		}
		i++;
	}
	return (0);
}

char    *cut_helper(const char *str)
{
    int     i;
    char    *rstr;

    i = ft_strlen(str) - 1;
    rstr = (char *)malloc(i + 2);
    if (str[i] == '/')
        i--;
    while (i >= 0 && str[i] != '/')
        i--;
    ft_strlcpy(rstr, str, i + 1);
    printf("---> rstr: %s\n", rstr); //? yeni konum
    return (rstr);
}

int	cd_func(int i)
{
    char	*home = getenv("HOME");
    char	path[1024];
    int     a;
    char	*p;

    if (getcwd(path, sizeof(path)) == NULL)
        printf("---> Path error\n");
    else if (strequal(g_var.str[i], "pwd"))
        printf("%s\n", path);
    else if (strequal(g_var.str[i + 1], ".."))
    {
		printf("---> path %s\n", path);
        p = cut_helper(path);
        a = chdir(p);
    }
	else if (g_var.str[i + 1])
	{
		if (strequal(g_var.str[i + 1], "~")) // ana dizine çıkma ve ana dizinden farklı bir dizine ulaşmak için
		{
			if (ft_strlen(g_var.str[i + 1]) > 1)
			{
				p = ft_strjoin(home, g_var.str[i + 1] + 1);
				a = chdir(p);

			}
			else
				a = chdir(home);
		}
		else // cd ile, ileri gitme bölümü
		{
			p = ft_strjoin(path, "/");
			p = ft_strjoin(p, g_var.str[i + 1]);
			printf("yeni dizin: %s\n", p);
			a = chdir(p);
			free(p);
		}
	}
	else
		chdir(home);
	printf("** cd işlem sonucu: %s\n", getcwd(path, sizeof(path)));
	
	if (g_var.pwd_new)
	{	
		free(g_var.pwd_new);
		g_var.pwd_new = NULL;
	}
	if (a == -1)
		g_var.pwd_new = ft_strjoin("PWD=", "/");
	else
		g_var.pwd_new = ft_strjoin("PWD=", p);
    return 0;
}
