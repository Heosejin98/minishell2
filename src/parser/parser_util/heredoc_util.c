#include "../../../include/minishell.h"

void	heredoc_unlink(void)
{
	int		hd_cnt;
	char	*filename;
	char	*temp;

	hd_cnt = 1;
	while (hd_cnt <= g_system_var.hd_cnt)
	{
		temp = ft_itoa(g_system_var.hd_cnt);
		filename = ft_strjoin("here_doc", temp);
		free(temp);
		if (access(filename, F_OK) == 0)
			unlink(filename);
		free(filename);
		hd_cnt++;
	}
}

void	heredoc_signal2(int sig)
{
	if (sig == SIGINT)
	{	
		g_system_var.hd_flag = 1;
	}
}
