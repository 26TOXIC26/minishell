#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	char *client;
	struct s_data *left;
	struct s_data *right;
}	t_data;

t_data *creat_node(char *client, t_data *left, t_data *right)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->client = client;
	data->left = left;
	data->right = right;
	return (data);
}

void printer(t_data *data)
{
	if (!data)
		return ;
	printf("%s", data->client);
	printer(data->left);
	printer(data->right);
}

int main()
{
	t_data *data;
	
	data = creat_node("\n\n   L3ZAWA\n", creat_node("Ara     ", NULL, NULL), creat_node("wekan\n\n", NULL, NULL));
	if (!data)
		return (1);
	printer(data);
	free(data);
}
