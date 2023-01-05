#include "../../include/minishell.h"
#include "../../include/token.h"

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
	{	
		g_system_var.hd_flag = 1;
		write(2, "\n", 1);
		heredoc_unlink();
		exit(EXIT_FAILURE);
	}
}

int	check_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WCOREFLAG | WTERMSIG(status));
}

void	print_error(char *err_msg1, char *err_msg2)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(err_msg1, STDERR_FILENO);
	ft_putendl_fd(err_msg2, STDERR_FILENO);
}

static void	heredoc_child(char *end_str, int hd_num)
{
	int		hd_fd;
	char	*line;
	char	*hd_filename;
	char	*temp;

	temp = ft_itoa(hd_num);
	hd_filename = ft_strjoin("here_doc", temp);
	free(temp);
	hd_fd = open(hd_filename, O_CREAT | O_RDWR | O_TRUNC, 0744);
	if (hd_fd == -1)
	{
		print_error(hd_filename, ": No such file or directory");
		exit(EXIT_FAILURE);
	}
	line = readline("> ");
	while (line && ft_strncmp(line, end_str, ft_strlen(line)) != 0)
	{
		if (ft_strchr(line, '$'))
			line = convert_env(line);
		ft_putstr_fd(line, hd_fd);
		ft_putstr_fd("\n", hd_fd);
		free(line);
		line = readline("> ");
	}
	close(hd_fd);
	exit(EXIT_SUCCESS);
}

void	heredoc_file_maker(char *end_str, int hd_num)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, heredoc_signal);
		heredoc_child(end_str, hd_num);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, heredoc_signal2);
		waitpid(pid, &pid, 0);
	}
}
