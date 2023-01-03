#include "minishell.h"

void	ft_exit(char **cmds)
{
	//0개일 때
	if (!cmds[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(0);
	}
	//exit code 확인
	if (!ft_isdigit(*cmds[1])) //문자열이 숫자인지 확인하는 함수로 변경
	{
		ft_putstr_fd("minish: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmds[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		g_system_var.status = 2;
		return ;
	}
	if (cmds[2])
	{
		ft_putstr_fd("minish: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmds[1], STDERR_FILENO);
		ft_putendl_fd(": too many arguments", STDERR_FILENO);
		g_system_var.status = 2;
		return ;
	}
	//3개 이상
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(*cmds[1] - '0'); //내 atoi 가져오기
	g_system_var.status = 0;
}