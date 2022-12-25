/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 14:54:53 by seheo             #+#    #+#             */
/*   Updated: 2022/12/24 23:35:14 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_system_var(char **envp)
{
	(void)envp;
	g_system_var.hd_cnt = 0;
	g_system_var.status = 0;
	g_system_var.old_std_fdin = dup(STDIN_FILENO);
	g_system_var.old_std_fdout = dup(STDOUT_FILENO);
	g_system_var.env = get_env(envp);
}

static void	minishell_start(void)
{
	char	*cmd_line;

	while (1)
	{
		cmd_line = readline("minishell$ ");
	}
}

int	ft_isalp_or_num(int c)
{	
	if ((c >= '0' && c <= '9'))
		return (1);
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

char *convert_env(const char *s)
{
	int start;
	int key_end;
	char *result;
	char *key;

	start = 0;
	while (s[start] != '$')
		start++;
	result = ft_substr1(s, 0, start);
	key_end = start + 1;
	while (ft_isalp_or_num(s[key_end]))
		key_end++;
	key = ft_substr(s, start + 1, key_end);

	if (dictionary_search(g_system_var.env, key) != NULL)
		result = ft_strjoin(result, dictionary_search(g_system_var.env, key));
	else{
		result = ft_strjoin(result, ft_substr1(s, start, ft_strlen(s)));
		return (result);
	}
		
	free(key);

	int end;

	end = key_end;
	while (s[end])
		end++;
	result = ft_strjoin(result, ft_substr1(s, key_end, end));

	return (result);

}

int	main(int argc, char **argv1, char **envp)
{
	(void)argc;
	(void)argv1;
	init_system_var(envp);

	char *dest;

	dest = convert_env("asd $PATHASDSD asd");

	printf("%s", dest);
/*
	t_deque buf;


    char **argv = ft_split("asd \"1\"\"1\" \"1\" qwe123", ' ');

	buf = make_tokens(argv);

	int i = 0;
	while (!is_empty(buf))
	{
		t_token t = output_front(&buf);
		while (t.cmdline[i])
		{
			printf("%s \n", t.cmdline[i]);
			i++;
		}
	}
	

/*
	//minishell_start();

	//parser_controller("ls -a -l >> a < b > c       | grep \"  asdasdass   1\" | cat << x > y");	
	//parser_controller("echo asdb \"\" asdwqe123 asdas \"c   \"");

        char *path = "/bin/echo";



        printf("execv호출\n");
        execv(path, argv);

        //printf("execle호출\n");
        //execle(path, file, arg1, arg2, NULL, NULL);

        //printf("execve호출\n");
        //execve(path, argv, NULL);

        //printf("execlp호출\n");
        //execlp(file, file, arg1, arg2, NULL);

        //printf("execvp호출\n");
        //execvp(file,argv);

        //printf("execvpe호출\n");
        //execvpe(file,argv,NULL);
		*/
}