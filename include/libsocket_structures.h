/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:34:52 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 15:49:27 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_STRUCTURES_H
# define LIBSOCKET_STRUCTURES_H

# ifndef __cplusplus

# include "libsocket_enums.h"

# include "libft.h"

typedef struct timeval		t_timeval;

typedef struct				s_addr
{
	struct sockaddr_storage	addr;
	socklen_t				len;
	char					*str;
}							t_addr;

typedef struct				s_method
{
	t_protocol				protocol;
	t_domain				domain;
}							t_method;

typedef struct				s_client
{
	int						fd;
	t_addr					addr;
	t_timeval				last;
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
	t_timeval				timeout;
	uint64_t				read_size;
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
