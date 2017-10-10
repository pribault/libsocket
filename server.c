/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 13:28:13 by pribault          #+#    #+#             */
/*   Updated: 2017/10/08 17:32:29 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket.h"

void	loop(t_server *server)
{
	t_pack	*pack;

	while (1)
	{
		while ((pack = receive_server(server)))
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
	t_server	*server;
	char		*line;
	pthread_t	thread;
	t_pack		pack;

	if (argc != 2)
		return (1);
	if (!(server = new_server(argv[1], UDP)))
		ft_printf("cannot create server\n");
	if (!start_server(server) || !start_server_autocleaner(server))
		ft_printf("cannot start server\n");
	set_server_refresh_rate(server, 1000);
	set_server_timeout(server, 30);
	pthread_create(&thread, NULL, (void*)&loop, server);
	while (ft_get_next_line(1, &line))
	{
		if (ft_strlen(line) > 5 && !ft_strncmp(line, "send ", 5) && server->clients->n)
			ft_printf("%lu sended\n", send_server(server, ft_vector_get(server->clients, 0), line + 5, ft_strlen(line + 5) + 1));
		free(line);
	}
	pthread_cancel(thread);
	free(line);
	stop_server_autocleaner(server);
	stop_server(server);
	destroy_server(server);
	return (0);
}
