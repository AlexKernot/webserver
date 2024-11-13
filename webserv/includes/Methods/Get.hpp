/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 21:10:20 by akernot           #+#    #+#             */
/*   Updated: 2024/03/03 23:09:23 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_HPP
# define GET_HPP

# include "../AHttpRequest.hpp"

class Get : public AHttpRequest {
public:
	Ahttp *serve(Config &config);
	std::string getMethodString() const;
	Config::methods getMethod() const;
private:
	Ahttp *autoIndex(std::string directoryPath) const;
};

#endif // GET_HPP
