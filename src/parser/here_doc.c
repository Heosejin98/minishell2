#include "../../include/minishell.h"

void	redir_unlink(void)
{
	int		hd_cnt;
	char	*filename;

	hd_cnt = 1;
	while (hd_cnt <= g_system_var.hd_cnt)
	{
		filename = ft_strjoin("here_doc", ft_itoa(hd_cnt));
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		hd_cnt++;
	}
}

void	sig_here_doc(int sig)
{

	if (sig == SIGINT)
	{	
		rl_replace_line("", 0);
		write(1, "\n", 2);
		rl_on_new_line();
		redir_unlink();
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

static void	redir_here_doc_child(char *end_str, int hd_num)
{
	int		hd_fd;
	char	*line;
	char	*hd_filename;

	signal(SIGINT, SIG_DFL);
	hd_filename = ft_strjoin("here_doc", ft_itoa(hd_num));
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


void	redir_here_doc_file(char *end_str, int hd_num)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, sig_here_doc);
		redir_here_doc_child(end_str, hd_num);
		exit(EXIT_FAILURE);
	}
	else
	{
		signal(SIGINT, sig_here_doc);
		waitpid(pid, &pid, 0);
		if (check_status(pid) == 130)
			exit(EXIT_FAILURE);
	}
}
