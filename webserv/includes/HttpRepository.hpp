/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRepository.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:07:30 by akernot           #+#    #+#             */
/*   Updated: 2024/05/24 20:37:42 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_REPOSITORY_HPP
# define HTTP_REPOSITORY_HPP

#include <queue>

#include <Ahttp.hpp>

class HttpRepository {
public:
	HttpRepository();
	~HttpRepository();

	void create(std::string text);
	void read();
	void update();
	void delete();
private:
	std::queue<Ahttp *> requests;
};

#endif