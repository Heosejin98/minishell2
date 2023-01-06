/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seheo <seheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:15:14 by seheo             #+#    #+#             */
/*   Updated: 2023/01/06 12:15:14 by seheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	ft_pwd(char **cmds);
void	ft_env(char **cmds);
void	ft_export(char **cmds);
void	ft_unset(char **cmds);
void	ft_cd(char **cmds);
void	ft_echo(char **cmds);
void	ft_exit(char **cmds);

int		is_option(char *line);
char	abstract_opt(char *line);
int		check_valid_opt(char **cmds, char opt, char *usage);
void	perror_opt(char *cmd, char opt, char *usage);
int		is_builtin(char *cmd);

#endif