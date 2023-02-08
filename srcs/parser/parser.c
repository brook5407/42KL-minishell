/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:42:56 by wricky-t          #+#    #+#             */
/*   Updated: 2023/02/07 21:22:06 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Skip to the next simple command block
 * 
 * @details
 * Iterate through the linked list and check if the value
 * stored inside the token struct is a PIPE. If yes, return
 * that address.
 * If not found, the while loop will continue until it hits
 * NULL. So just return NULL.
 * In parser, when this function return NULL, it means
 * the whole parsing process is terminated.
*/
t_list	*skip_to_next_cmd_block(t_list *curr, t_parser *hlpr)
{
	t_list	*new_start;
	t_token	*token;

	new_start = curr;
	while (new_start != NULL)
	{
		token = new_start->content;
		if (ft_strcmp(token->value, "|") == 0 && token->type == PIPE)
		{
			hlpr->curr_grammar = START;
			return (new_start->next);
		}
		new_start = new_start->next;
	}
	hlpr->curr_grammar = FREE_FORM;
	return (new_start);
}

/**
 * @brief Grammar checker. Checks the token if it's expected. If not expected,
 * 		  identify the error type.
 * 
 * @details
 * There are two use case for grammar checker:
 * i. When iterate through the token list to check if a token is expected
 * 	  or accepted by the grammar. (token is NOT NULL)
 * ii. To check the ending of a "simple command" (token is NULL)
 * 
 * By default, grammar checker assume the token is acceptable, hence status
 * is SUCCESS. The "unexpected" variable is used to store the unexpected
 * token so that can be outputted to the screen if there's an error.
 * 
 * Use case (i):
 * If the token is not expected, there are two possible error. Either it's
 * SYNTAX_ERROR or CMD_NOT_FOUND. CMD_NOT_FOUND occurs when the token is a
 * STR and the grammar does not accept any STR. SYNTAX ERROR occurs when
 * the grammar is POST_RDR, which the following token should either be
 * EXT_CMD, CMD or STR but it's other type.
 * 
 * Use case (ii):
 * Since we only add the cmd block to the cmd list when we encounter a PIPE,
 * which means if we already iterated through the token list, the current
 * cmd block in parser will not be added into the cmd list. Hence, if that's
 * the case, check the grammar to see if it's POST_RDR (meaning it ends
 * with redirections) or START (meaning it ends with PIPE).
 * 
 * When there's SYNTAX ERROR or CMD_NOT_FOUND, all the cmd in cmd list will
 * be freed and the parser will be reset.
 * 
 * This function will return the status of grammar_checker, whether it's
 * SUCCESS, CMD_NOT_FOUND or SYNTAX_ERROR.
 */
int	grammar_checker(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	t_grammar	gram;
	int			status;
	char		*unexpected;

	status = SUCCESS;
	gram = hlpr->curr_grammar;
	unexpected = NULL;
	if (token == NULL && (gram == POST_RDR || gram == START))
		status = SYNTAX_ERROR;
	else if (token != NULL && is_type_on(hlpr, token->type) == 0)
	{
		// if ((gram == START || gram == CMD_ONLY) && token->type == STR)
		if (gram == START && token->type == STR)
			status = CMD_NOT_FOUND;
		else if ((gram == START && token->type == PIPE) || gram == POST_RDR)
			status = SYNTAX_ERROR;
		unexpected = token->value;
	}
	if (status == SYNTAX_ERROR)
	{
		show_error(status, unexpected);
		init_parser(hlpr);
		ft_lstclear(&ms->cmds, free_cmd_block);
	}
	return (status);
}

void	resolve_loop(t_minishell *ms, t_list **curr, t_parser *hlpr)
{
	t_list	*lst;
	t_token	*token;

	lst = *curr;
	while (lst != NULL)
	{
		token = lst->content;
		if (token->type == PIPE)
		{
			lst = lst->next;
			break ;
		}
		builder(ms, hlpr, token);
		set_next_grammar(hlpr, token->type);
		lst = lst->next;
	}
}

void	resolve_cmd_not_found(t_minishell *ms, t_list **curr, t_parser *hlpr)
{
	t_list	*lst;

	lst = *curr;
	((t_token *)lst->content)->type = CMD;
	resolve_loop(ms, curr, hlpr);
	exec_redirt_in(ms, &hlpr->cmd);
	exec_redirt_out(&hlpr->cmd);
	// need to reset the io back
	show_error(CMD_NOT_FOUND, hlpr->cmd.cmd_name);
	free_cmd_data(&hlpr->cmd);
	init_parser(hlpr);
	ft_lstclear(&ms->cmds, free_cmd_block);
	hlpr->curr_grammar = FREE_FORM;
	*curr = lst;
}

/**
 * @brief Parse the list of token and build a cmd list
 * 
 * @details
 * 1. Initialize the parser. The parser is designed to process one
 * 	  "simple command" block at a time. Once encounter a pipe or at
 *    the end of the token list, add the cmd block to the cmd list
 * 2. Iterate through the token list and while iterating through,
 * 		i.		Check the grammar of the current token
 * 		ii.		Build the cmd block
 * 		iii.	Set the next grammar to ensure that the next token
 * 				is expected
 * 3. When iterating through the token list, it's possible that there
 * 	  is no pipe in it, which means the cmd block we are builting might
 *    not be able to add into the cmd list. So when reach the end of
 *    token list, add the cmd block we are builting into the cmd list.
 */
void	parser(t_minishell *ms)
{
	t_list		*token_lst;
	t_parser	hlpr;
	int			status;

	token_lst = ms->tokens;
	init_parser(&hlpr);
	while (token_lst != NULL)
	{
		status = grammar_checker(ms, &hlpr, token_lst->content);
		if (status == SYNTAX_ERROR)
			return ;
		else if (status == CMD_NOT_FOUND)
		{
			resolve_cmd_not_found(ms, &token_lst, &hlpr);
			continue ;
		}
		builder(ms, &hlpr, token_lst->content);
		set_next_grammar(&hlpr, ((t_token *)token_lst->content)->type);
		token_lst = token_lst->next;
	}
	status = grammar_checker(ms, &hlpr, NULL);
	if (status != SYNTAX_ERROR && status != CMD_NOT_FOUND)
		add_as_cmd_block(ms, &hlpr);
}
