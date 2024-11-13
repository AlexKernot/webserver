/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IServible.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:48:13 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 18:14:27 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ISERVIBLE_HPP
# define ISERVIBLE_HPP

# include "Ahttp.hpp"
# include "Config.hpp"

class IServible {
public:
	virtual Ahttp *serve(Config &config) = 0;
	virtual ~IServible() {}
};

#endif // ISERVIBLE_HPP
