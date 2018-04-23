/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_callbacks.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:27:29 by pribault          #+#    #+#             */
/*   Updated: 2018/04/20 14:47:44 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_CALLBACKS_HPP
# define LIBSOCKET_CALLBACKS_HPP

# ifdef __cplusplus

#  include "libsocket_message.hpp"
#  include "libsocket_client.hpp"

namespace libsocket
{
	class	Socket;

	class	Callbacks
	{
		public:

			virtual void	client_add(Socket& socket, Client& client);
			virtual void	client_del(Socket&, Client&);
			virtual void	msg_recv(Socket&, Client&, Message&);
			virtual void	msg_send(Socket&, Client&, Message&);
			virtual void	msg_trash(Socket&, Client&, Message&);
			virtual void	client_excpt(Socket&, Client&);
			virtual void	socket_bind(Socket&);
			virtual void	socket_unbind(Socket&);
			virtual void	socket_excpt(Socket&);
			virtual void	buffer_full(Socket&);
	};
}

# else

#  error "c++ only header"

# endif

#endif
