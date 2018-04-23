/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pribault <pribault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 11:21:01 by pribault          #+#    #+#             */
/*   Updated: 2018/04/20 14:25:12 by pribault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsocket_message.hpp"

using namespace	libsocket;

Message::Message(void)
{
	null_terminated = false;
}

Message::Message(std::string& string)
{
	uint64_t	size;

	size = string.length() + 1;
	vector.resize(size);
	memcpy(&vector[0], (void*)string.c_str(), size);
	null_terminated = true;
}

Message::Message(void *ptr, uint64_t size)
{
	vector.resize(size);
	memcpy(&vector[0], ptr, size);
	null_terminated = false;
}

Message::~Message(void)
{
}

Message&	Message::operator=(Message& message)
{
	uint64_t	size;

	size = message.vector.size();
	vector.resize(size);
	memcpy(&vector[0], &message.vector[0], size);
	null_terminated = false;
	return (*this);
}

Message&	Message::operator=(std::string string)
{
	uint64_t	size;

	size = string.length() + 1;
	vector.resize(size);
	memcpy(&vector[0], (void*)string.c_str(), size);
	null_terminated = true;
	return (*this);
}

Message&	Message::operator=(std::string& string)
{
	uint64_t	size;

	size = string.length() + 1;
	vector.resize(size);
	memcpy(&vector[0], (void*)string.c_str(), size);
	null_terminated = true;
	return (*this);
}

Message&	Message::operator+=(Message& message)
{
	uint64_t	size[2];

	size[0] = vector.size();
	size[1] = message.vector.size();
	vector.resize(size[0] + size[1]);
	memcpy(&vector[size[0]], &message.vector[0], size[1]);
	null_terminated = false;
	return (*this);
}

Message&	Message::operator+=(std::string string)
{
	uint64_t	size[2];

	if (null_terminated == true)
		size[0] = vector.size() - 1;
	else
		size[0] = vector.size();
	size[1] = string.length() + 1;
	vector.resize(size[0] + size[1]);
	memcpy(&vector[size[0]], string.c_str(), size[1]);
	null_terminated = true;
	return (*this);
}

Message&	Message::operator+=(std::string& string)
{
	uint64_t	size[2];

	if (null_terminated == true)
		size[0] = vector.size() - 1;
	else
		size[0] = vector.size();
	size[1] = string.length() + 1;
	vector.resize(size[0] + size[1]);
	memcpy(&vector[size[0]], string.c_str(), size[1]);
	null_terminated = true;
	return (*this);
}

Message&	Message::append(Message& message)
{
	uint64_t	size[2];

	size[0] = vector.size();
	size[1] = message.vector.size();
	vector.resize(size[0] + size[1]);
	memcpy(&vector[size[0]], &message.vector[0], size[1]);
	null_terminated = false;
	return (*this);
}

Message&	Message::append(std::string string)
{
	uint64_t	size[2];

	if (null_terminated == true)
		size[0] = vector.size() - 1;
	else
		size[0] = vector.size();
	size[1] = string.length() + 1;
	vector.resize(size[0] + size[1]);
	memcpy(&vector[size[0]], string.c_str(), size[1]);
	null_terminated = true;
	return (*this);
}

Message&	Message::append(std::string& string)
{
	uint64_t	size[2];

	if (null_terminated == true)
		size[0] = vector.size() - 1;
	else
		size[0] = vector.size();
	size[1] = string.length() + 1;
	vector.resize(size[0] + size[1]);
	memcpy(&vector[size[0]], string.c_str(), size[1]);
	null_terminated = true;
	return (*this);
}

Message&	Message::append(void *ptr, uint64_t size)
{
	uint64_t	msize;

	msize = vector.size();
	vector.resize(msize + size);
	memcpy(&vector[msize], ptr, size);
	null_terminated = false;
	return (*this);
}

void	Message::debug(void)
{
	uint64_t	i;

	for (i = 0; i < vector.size(); i++)
	{
		if (!((i + 1) % 8))
			printf("%hhx\n", vector[i]);
		else
			printf("%hhx ", vector[i]);
	}
	if (i % 8)
		printf("\n");
}

void	Message::print(void)
{
	printf("%s\n", &vector[0]);
}
