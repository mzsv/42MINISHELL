#include "../../includes/minishell.h"
#include "../../includes/expander.h"

void print_lexer_list(t_lexer_token *list);
static void print_commands_list(t_command *list)
{
	int  i = 0;

	while (list)
	{
		printf("Element index %d\n", i);
		i++;
		char **s = list->str;
		if (!s || !(*s)) {
			printf("Arguments list in empty\n");
			list = list->next;
			continue;
		}
		while (*s) {
			printf("%s ", *s);
			s++;
		}
		printf("\n");
		printf("Redirs list: \n");
		print_lexer_list(list->redirs);
		printf("\n\n");
		list = list->next;
	}
}

static void print_parser_info(t_app *app)
{
	printf("	=== Parser Info ===	\n");
	printf("Pipes count %d\n\n", app->pipes_count);
	print_commands_list(app->commands_list);
}

void parser_test(t_app *app)
{
	int status = parser(app);

	expander(app);

	if (status == EXIT_SUCCESS)
		print_parser_info(app);
}
