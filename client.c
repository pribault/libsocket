/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:28:16 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 16:51:09 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	loop(t_client *client)
{
	t_pack	*pack;

	while (1)
	{
		while ((pack = receive_client(client)))
		{
			ft_putstr("receive: ");
			write(1, &pack->data, pack->size);
			ft_putchar('\n');
		}
		sleep(1);
	}
}

int		main(int argc, char **argv)
{
	t_client	*client;
	t_pack		*pack;
	char		*line;
	pthread_t	thread;

	if (argc != 3)
		return (1);
	if (!(client = new_client(argv[1], argv[2], UDP)))
		ft_printf("cannot create client\n");
	if (!start_client(client))
		ft_printf("cannot start client\n");
	pthread_create(&thread, NULL, (void*)&loop, client);
	while (ft_get_next_line(1, &line))
	{
		if (ft_strlen(line) > 5 && !ft_strncmp(line, "send ", 5))
		{
			ft_printf("%lu sended\n", send_client(client, line + 5, ft_strlen(line + 5) + 1));
		}
		free(line);
	}
	pthread_cancel(thread);
	free(line);
	stop_client(client);
	destroy_client(client);
	return (0);
}
