/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:42:56 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/08 18:15:17 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * TODO:
 * 1. A function to iterate through the token list and parse [V]
 * 2. A function that expect a token. If the token is not expected, meaning
 *    grammar is wrong. [V]
 * 		a. First token of a grammar can be either a command, redirection.
 * 		b. The token after a redirection confirm is a file. The next token
 *         of redirection must be a [STR], cannot be a pipe.
 * 		c. After a file, can be pipe, another redirection, argument.
 *         If the argument list is empty, the [STR] could be the command.
 *      d. Pipe marks a new beginning of a simple grammar.
 * 3. A struct as a parser helper. [V]
 * 4. Error handler. Show error based on the incorrect grammar.
 */

/**
 * Parser process
 *
 * 1. Initialize parser_helper (should pass to a grammar checker in every
 *    iteration)
 * 2. Iterate through the token_list
 * 3. In each iteration
 * 		i.	 Get the type of that token
 *      ii.	 Check if the token match what's expected
 *      iii. If...
 * 			 a. ... it's expected
 * 				- save it into the node
 * 					- based on the grammar, where to stored the value
 * 					  will be different as well (check previous token)
 * 				- set next's token grammar rules
 * 				- move on to the next token
 *           b. ... it's not expected
 * 				- handle error
 *              - stop the current cmd block, move to the end
 * 					- might have to free what's been saved in the node
 *              - or stop when there's another pipeline and start
 *                parsing again.
 * 4. At the end of the whole process, the output is a cmd_list
 *
 * IDEA:
 * 2. Create a function that visualize each node in cmd_list
 * 3. Create functions that help building the cmd_list (builder functions)
 */

/**
 * When the grammar is:
 * 1. START
 * 		- the token is STR means cmd not found
 * 		- the token is PIPE means parse error
 * 2. POST_RDR
 * 		- Any redirection token (>, <, <<, >>) means parser error
 * 		- PIPE means parse error
 * 		- Basically means if the following token is not expected, it's parse error
 * 3. CMD_ONLY
 * 		- If token is a STR, meaning cmd not found
*/

/**
 * @brief Grammar checker. Checks the token if it's expected. If not expected,
 * 		  identify the error type.
 * 
 * @details
 * Firstly, check if the current token type is on in the current grammar. If
 * yes, return 1 indicating grammar no error. The rest of the procedure will
 * be to identify which error type.
 * If the grammar is START or CMD_ONLY and the current token type is a STR,
 * meaning it's a CMD_NOT_FOUND error.
 * If the grammar is POST_RDR and anything passed in is not expected, it's a
 * SYNTAX ERROR. Or if the grammar is START and the type is PIPE.
 * 
 * According to Bash behavior on CMD_NOT_FOUND & SYNTAX ERROR, when encounter
 * CMD_NOT_FOUND, the shell should continue parse what's behind the pipe if have.
 * When encounter SYNTAX_ERROR, stop parsing and do not execute anything. Also,
 * when any of these happens, output the error in STDERR.
 * 
 * Since the executor will try to iterate through the cmd list, and to let
 * executor don't execute, the best way would probably be clearing out the
 * cmd list so that executor won't even run.
 * 
 * And since parser will process one cmd block at a time, if any error happens,
 * clear up the current processed cmd block as well. So that it won't be added
 * into the cmd list and get executed.
 * 
 * If you look at the parser function, there are two calls of grammar_checker.
 * The first call has already explained above. How about the second call? The
 * second call is to make sure that the processed command list does not
 * end with unexpected token like redirection and pipe.
 * 
 * Since we are checking the end of the cmd list, there's nothing to deal with
 * the token. We just have to check the grammar at the end is what's expected.
 * If the cmd_list ends with PIPE, meaning the next grammar should be START.
 * If the cmd_list ends with Redirections, meaning the next grammar should be
 * POST_RDR.
 * Hence, if the ending grammar is either one, it's a SYNTAX_ERROR.
 * Whatever has been stored inside the cmd list should be discarded and the 
 * current cmd block should be freed as well.
*/
int	grammar_checker(t_minishell *ms, t_parser *hlpr, t_token *token)
{
	t_grammar		gram;
	int				error;

	gram = hlpr->curr_grammar;
	error = SUCCESS;
	if (token != NULL)
	{
		if (is_type_on(hlpr, token->type) == 1)
			return (error);
		if ((gram == START || gram == CMD_ONLY) && token->type == STR)
			error = CMD_NOT_FOUND;
		else if ((gram == START && token->type == PIPE) || gram == POST_RDR)
			error = SYNTAX_ERROR;
		show_error(error, token->value);
		free_cmd_block((void *)hlpr->cmd);
	}
	else
	{
		if (gram == POST_RDR || gram == START)
			error = SYNTAX_ERROR;
		show_error(error, NULL);
	}
	ft_lstclear(&ms->cmds, free_cmd_block);
	return (error);
}

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
t_list	*skip_to_next_cmd_block(t_list *curr)
{
	t_list	*new_start;
	t_token	*token;

	new_start = curr;
	while (new_start != NULL)
	{
		token = new_start->content;
		if (ft_strcmp(token->value, "|") == 0 && token->type == PIPE)
			return (new_start->next);
		new_start = new_start->next;
	}
	return (NULL);
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
 * 	  is no pipe in it, which means the cmd block we are building might
 *    not be able to add into the cmd list. So when reach the end of
 *    token list, add the cmd block we are building into the cmd list.
 */
/** TODO: Make parser to return a value so that the main function could
 * do something about it
*/
void	parser(t_minishell *ms)
{
	t_token		*token;
	t_list		*token_lst;
	t_parser	hlpr;
	int			error;

	token_lst = ms->tokens;
	init_parser(&hlpr);
	while (token_lst != NULL)
	{
		token = token_lst->content;
		error = grammar_checker(ms, &hlpr, token);
		if (error == SYNTAX_ERROR)
			return ;
		else if (error == CMD_NOT_FOUND)
		{
			token_lst = skip_to_next_cmd_block(token_lst);
			continue ;
		}
		builder_helper(ms, &hlpr, token);
		set_next_grammar(&hlpr, token->type);
		token_lst = token_lst->next;
	}
	grammar_checker(ms, &hlpr, NULL);
	add_as_cmd_block(ms, &hlpr);
}
