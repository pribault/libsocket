/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsocket_Callbacks.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:27:29 by pribault          #+#    #+#             */
/*   Updated: 2018/04/19 13:28:25 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSOCKET_CALLBACKS_HPP
# define LIBSOCKET_CALLBACKS_HPP

namespace libsocket
{
	template	<typename CB>
	class	Callbacks
	{
		public:

			virtual void	client_add(Socket<CB>& socket, Client& client);
			virtual void	client_del(Socket<CB>&, Client&);
			virtual void	msg_recv(Socket<CB>&, Client&, t_msg&);
			virtual void	msg_send(Socket<CB>&, Client&, t_msg&);
			virtual void	msg_trash(Socket<CB>&, Client&, t_msg&);
			virtual void	client_excpt(Socket<CB>&, Client&);
			virtual void	socket_bind(Socket<CB>&);
			virtual void	socket_unbind(Socket<CB>&);
			virtual void	socket_excpt(Socket<CB>&);
			virtual void	buffer_full(Socket<CB>&);
	};
};

#endif
