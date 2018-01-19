/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 11:15:22 by pribault          #+#    #+#             */
/*   Updated: 2018/01/19 09:02:24 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_H
# define LIBSOCKET_H

/*
****************
**	includes  **
****************
*/

# include <sys/socket.h>
# include <unistd.h>

/*
*************
**	types  **
*************
*/

/*
**	enums
*/

typedef enum	e_protocol
{
	TCP = SOCK_STREAM,
	UDP = SOCK_DGRAM
}				t_protocol;

typedef void	*t_client;
typedef void	*t_server;

/*
************************
**	client functions  **
************************
*/

t_client				*client_new(t_protocol protocol,
						char *address, char *port);

/*
************************
**	server functions  **
************************
*/

t_server				*server_new(void);
void					server_delete(t_server **server);
int						server_start(t_server *server, t_protocol protocol,
						char *port);
void					server_stop(t_server *server);

#endif
