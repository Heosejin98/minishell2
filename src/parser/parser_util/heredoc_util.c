#include "../../../include/minishell.h"

void	heredoc_unlink(void)
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
