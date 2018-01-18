#include "libsocket.h"

t_server	*new_server_tcp(t_server *server, char *port)
{
	(void)server;
	(void)port;
	return (NULL);
}

t_server	*new_server_udp(t_server *server, char *port)
{
	(void)server;
	(void)port;
	return (NULL);
}

t_server	*new_server(t_protocol protocol, char *port)
{
	t_server	*server;

	if (!(server = (t_server*)malloc(sizeof(t_server))))
		return (NULL);
	if (protocol == TCP)
		return (new_server_tcp(server, port));
	else if (protocol == UDP)
		return (new_server_udp(server, port));
	else
		free(server);
	return (NULL);
}
