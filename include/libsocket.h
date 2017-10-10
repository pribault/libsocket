/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2017/10/10 21:01:49 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_H
# define LIBSOCKET_H

/*
**	includes
**
**	waouh, includes, so awesome :o
*/

# include "libft.h"
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <pthread.h>
# include <errno.h>

/*
**	our defines <3
*/

# define PACKAGE_SIZE_MAX	0x100

# define TCP				SOCK_STREAM
# define UDP				SOCK_DGRAM

# define RECEIVER			0x1
# define AUTOCLEANER		0x2

/*
**	variables
*/

typedef struct addrinfo	t_addrinfo;
typedef struct sockaddr	t_sockaddr;

/*
**	structures
*/

typedef struct			s_id
{
	t_sockaddr			addr;
	socklen_t			addr_len;
	time_t				last;
}						t_id;

typedef struct			s_pack
{
	char				data[PACKAGE_SIZE_MAX];
	size_t				size;
	t_id				id;
}						t_pack;

typedef struct			s_client
{
	t_addrinfo			*addresses;
	t_addrinfo			*addr;
	int					sockfd;
	int					protocol;
	pthread_t			receiver;
	pthread_mutex_t		receiver_mutex;
	pthread_t			autocleaner;
	pthread_mutex_t		autocleaner_mutex;
	t_vector			*waiting;
	size_t				refresh;
	size_t				timeout;
	int					running;
	time_t				last;
}						t_client;

typedef struct			s_server
{
	int					sockfd;
	int					protocol;
	pthread_t			receiver;
	pthread_mutex_t		receiver_mutex;
	pthread_t			autocleaner;
	pthread_mutex_t		autocleaner_mutex;
	t_vector			*waiting;
	t_vector			*clients;
	size_t				refresh;
	size_t				timeout;
	int					running;
}						t_server;

/*
**	client functions
*/

t_client				*new_client(char *ip, char *port, int prot);
int						destroy_client(t_client *client);

int						start_client(t_client *client);
int						stop_client(t_client *client);

int						set_client_refresh_rate(t_client *client,
						size_t microseconds);
int						set_client_timeout(t_client *client, size_t seconds);
int						start_client_autocleaner(t_client *client);
int						stop_client_autocleaner(t_client *client);

t_pack					*receive_client(t_client *client);
size_t					send_client(t_client *client, void *data, size_t size);

/*
**	server functions
*/

t_server				*new_server(char *port, int prot);
int						destroy_server(t_server *server);

int						start_server(t_server *server);
int						stop_server(t_server *server);

int						set_server_refresh_rate(t_server *server,
						size_t microseconds);
int						set_server_timeout(t_server *server, size_t seconds);
int						start_server_autocleaner(t_server *server);
int						stop_server_autocleaner(t_server *server);

t_pack					*receive_server(t_server *server);
size_t					send_server(t_server *server, t_id *id, void *data,
						size_t size);

#endif
