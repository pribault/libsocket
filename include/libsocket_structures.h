/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:34:52 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 11:13:28 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_STRUCTURES_H
# define LIBSOCKET_STRUCTURES_H

# ifndef __cplusplus

# include "libsocket_enums.h"

# include "libft.h"

typedef struct				s_method
{
	t_protocol				protocol;
	t_domain				domain;
}							t_method;

typedef struct				s_client
{
	int						fd;
	struct sockaddr_storage	addr;
	socklen_t				addr_len;
	struct timeval			last;
	void					*data;
	t_write_type			write_type;
}							t_client;

typedef struct				s_msg
{
	void					*ptr;
	uint64_t				size;
}							t_msg;

typedef struct				s_towrite
{
	t_client				client;
	t_msg					data;
}							t_towrite;

typedef struct				s_socket
{
	t_protocol				protocol;
	t_domain				domain;
	int						sockfd;
	int						queue_max;
	struct timeval			timeout;
	t_vector				clients;
	t_circ_buffer			write_queue;
	uint16_t				port;
	uint8_t					opt;
	void					*data;
	void					(*client_add)(struct s_socket *, t_client *);
	void					(*client_del)(struct s_socket *, t_client *);
	void					(*msg_recv)(struct s_socket *, t_client *,
							t_msg *);
	void					(*msg_send)(struct s_socket *, t_client *,
							t_msg *);
	void					(*msg_trash)(struct s_socket *, t_client *,
							t_msg *);
	void					(*client_excpt)(struct s_socket *, t_client *);
	void					(*socket_bind)(struct s_socket *);
	void					(*socket_unbind)(struct s_socket *);
	void					(*socket_excpt)(struct s_socket *);
	void					(*buffer_full)(struct s_socket *);
}							t_socket;

# else

#  pragma message __FILE__ "C only header"

# endif

#else

# pragma message __FILE__ "already included"

#endif
