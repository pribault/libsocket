/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 14:51:55 by pribault          #+#    #+#             */
/*   Updated: 2018/04/20 14:52:47 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket_socket.hpp"

using namespace	libsocket;

Socket::Socket(Callbacks callbacks)
{
	this->callbacks = callbacks;
}
