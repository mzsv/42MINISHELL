//
// Created by amitcul on 6/6/23.
//

#include "../../includes/minishell.h"
#include "../../includes/error.h"

static char *get_token_name(t_token_type type)
{
	if (type == WORD) {
		return "WORD";
	} else if (type == PIPE) {
		return ("PIPE");
	} else if (type == GREAT) {
		return ("GREAT");
	} else if (type == LESS) {
		return ("LESS");
	} else if (type == G_GREAT) {
		return ("Gec_GREAT");
	} else if (type == L_LESS) {
		return ("L_LESS");
	}
	return ("BLANK");
}

void print_lexer_list(t_lexer_token *list)
{
	if (!list) {
		printf("List is empty.\n");
		return ;
	}
	while (list)
	{
		printf("%zu %s %s\n", list->index, get_token_name(list->token_type), list->str);
		list = list->next;
	}
}

int lexer_test(t_app *app)
{
	char *inputs[2] = {
			"echo $PATH> <out || cat out",
			"echo >> >> $PATH << out"
	};
	for (size_t i = 0; inputs[i]; ++i) {
		printf("%zu\n", i);
		app->input = ft_strdup(inputs[i]);
		if (!check_quotes(app->input))
			return (ft_error(2, app));
		int status = get_tokens(app);
		if (status <= 0)
			return (ft_error(1, app));
		print_lexer_list(app->lexer_tokens);
		ft_lexerclear(&app->lexer_tokens);
	}
	return (0);
}


