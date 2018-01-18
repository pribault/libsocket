#include "libsocket.h"

t_client	*new_client_tcp(t_client *client, char *address, char *port)
{
	(void)client;
	(void)address;
	(void)port;
	return (NULL);
}

t_client	*new_client_udp(t_client *client, char *address, char *port)
{
	(void)client;
	(void)address;
	(void)port;
	return (NULL);
}

t_client	*new_client(t_protocol protocol, char *address, char *port)
{
	t_client	*client;

	if (!(client = (t_client*)malloc(sizeof(t_client))))
		return (NULL);
	if (protocol == TCP)
		return (new_client_tcp(client, address, port));
	else if (protocol == UDP)
		return (new_client_udp(client, address, port));
	else
		free(client);
	return (NULL);
}