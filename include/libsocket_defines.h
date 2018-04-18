/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_defines.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 13:38:02 by pribault          #+#    #+#             */
/*   Updated: 2018/04/18 11:15:50 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_DEFINES_H
# define LIBSOCKET_DEFINES_H

# ifndef __cplusplus

#  define METHOD(prot, dom)	(t_method){prot, dom}

/*
**	possible methods
*/

# ifdef LIBSOCKET_STRUCTURES_H

#  define TCP_IPV4	(t_method){TCP, IPV4}
#  define TCP_IPV6	(t_method){TCP, IPV6}
#  define UDP_IPV4	(t_method){UDP, IPV4}
#  define UDP_IPV6	(t_method){UDP, IPV6}

# else

#  pragma message "libsocket.h not included, partial defines"

# endif

/*
**	number of messages that can be enqueued to write in a socket
*/

#  define CIRCULAR_BUFFER_SIZE	128

/*
**	size of buffer used to read packets
*/

#  define READ_BUFFER_SIZE		512

/*
**	default values
*/

#  define SERVER_DEFAULT_QUEUE_MAX	2
#  define SERVER_DEFAULT_TIMEOUT_S	1
#  define SERVER_DEFAULT_TIMEOUT_US	0

/*
**	option masks
*/

# define SERVER_RUNNING		0x1

# else

#  pragma message __FILE__ "C only header"

# endif

#else

# pragma message __FILE__ "already included"

#endif
