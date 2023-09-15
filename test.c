
void	put_redirect(t_tokens *temp, int temp_id)
{
	if (!temp)
		ft_putstr_exit("Error: Malloc failed", 2, 1);
	temp->data->token_id = temp_id;
	if (temp_id == LESS || temp_id == LESSLESS)
		ex()->in = ft_lstadd_back(ex()->in, temp);
	else
		ex()->out = ft_lstadd_back(ex()->out, temp);
}

void	execute_cmds(t_tokens *t)
{
	t_tokens	*temp = NULL;
	int			temp_id;

	temp_id = 0;
	while (t)
	{
		if (t->data->token_id == PIPE && !temp)
			ft_putstr_exit("syntax error near unexpected token `|'", 2, 1);
		temp = ft_lstnew(t->data);
		if (!temp)
			ft_putstr_exit("Error: Malloc failed", 2, 1);
		if (t->data->token_id < 130)
			ex()->exec = ft_lstadd_back(ex()->exec, temp);
		else if (t->data->token_id == LESS)
		{
			ft_lstdelone(temp);
			t = t->next;
			if (t)
			{
				temp = ft_lstnew(t->data);
				if (!temp)
					ft_putstr_exit("Error: Malloc failed", 2, 1);
				ex()->in = ft_lstadd_back(ex()->in, temp);
			}
			else
				break ;
		}
		else if (t->data->token_id == LESSLESS)
			printf ("Do heredoc");
		else if (t->data->token_id == GREAT
			|| t->data->token_id == GREATGREAT)
		{
			temp_id = temp->data->token_id;
			ft_lstdelone(temp);
			t = t->next;
			if (t)
			{
				temp = ft_lstnew(t->data);
				if (!temp)
					ft_putstr_exit("Error: Malloc failed", 2, 1);
				temp->data->token_id = temp_id;
				ex()->out = ft_lstadd_back(ex()->out, temp);
			}
			else
				break ;
		}
		else if (t->data->token_id == PIPE)
			parent_process(t);
		t = t->next;
	}
	parent_process(t);
	close_tab(ex()->fd);
}