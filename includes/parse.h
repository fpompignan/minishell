/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fassier- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:41:35 by fassier-          #+#    #+#             */
/*   Updated: 2022/05/26 15:51:05 by fassier-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

//------split------
char		**f_split(char *str, char *charset);

//------utils-----------
int			f_strlen(char *str);
void		free_array(char **array);
char		*ft_strncpy(char *dst, const char *src, size_t len);
char		*ft_strndup_sp(char *s, int n, t_process *process);
char		*ft_strndup(char *s, int n);
char		*f_strdup(char *s);
int			ft_strcmp(char *s1, char *s2);
char		*f_strjoin(char *s1, char *s2);
char		*f_strjoin2(char *s1, char *s2);
int			forward_to_first_nonspace_char(char *str);
int			find_dollar(char *str);
int			get_nb_variable_env(char **env);
int			f_isalnum(char c);
char		*ft_replace(char *str, t_env *env);
int			has_quote(t_process process, int to, int dollar);
int			quote_after_var(t_process process, int num_token, int dollar);
int			find_dollar2(char *str);
int			has_quote_before(t_process process, int to, int dollar);
int			find_space(char *line);
t_process	manage(t_process process, int space, int to, int *brake);
t_process	manage2(t_process process, int space, int dollar, int to);
t_process	manage3(t_process process, int to, int dollar, int i);

//-----------exit---------------
void		exit_minishell(t_process *process);
void		free_process(t_process *process);
void		free_tokens(t_token *tokens);

//------get_nbre_process--------
int			get_nb_process(char *line);

//-----get_process_1-------
t_process	*get_process_init(char *line, t_process *process);
t_process	*get_process_str(char *line, t_process *process);
int			forward_to_next_quote(char *line, int i);

//-----put_space_between_redir-------
char		*put_space_close_redir(char *line);
int			count_operator(char *line);

//-----tab_word---------
char		**get_tab_word_for_token(char *line);

//-----get_token1-------
t_process	*get_token_init(t_process *process);
t_process	*get_token_word(t_process *process);
int			get_nb_tokens(t_process process);

//-------lexer---------------
t_process	*get_tokens(t_process *process, int *action);
t_process	*get_process(char *line, t_process *process);
t_process	*lexer(char *line, t_process *process, int *action);

//-------get_redirection_type--------------------------
t_process	get_operator(t_process process);
int			get_filename_type(t_process *process);

//-------get_functions-----------------
t_process	get_function(t_process process);

//----------quotes-----------
char		*remove_quotes_line(char *str);
t_process	remove_quotes(t_process process);

// ---------env-------------------
t_process	*get_realname_env(t_process *process, char **env);

//----------env2---------------
t_process	*get_var_env(t_process *process, char **env);

//-------get_var_env-----------
t_process	*lexer2(t_process *process);
int			quote_after_var(t_process process, int num_token, int dollar);

//------check_error_redir------------
int			check_error_redir(t_process *process);

//-----check_error_redir2--------------
int			return_err(int i, char c, char d);
int			check_chevron_r(t_process process, int i);
int			check_chevron_l(t_process process, int i);

//-------parse.c----------
t_process	*got_env(t_process *process, char **env);
int			get_tab_redir(t_process *process);
int			count_arg(t_process *process);
int			get_tab_arg(t_process *process);
int			parser(t_process *process);

//------------parser.c-------------------------
t_process	*parse(char *commande, char **env);

//--------get_tab_redirection---------
int			get_tab_redir(t_process *process);

//----------------replace--------------------
char		*ft_replace(char *str, t_env *env);

//---------------interrogation-----------
t_process	rep2(t_process process, int to, int dollar);
int			is_point_inter(t_process process, int to, int dollar);

//--------------space_in_var-----------------
int			has_space(char *line);
t_process	add_token(t_process process, int to);

#endif
