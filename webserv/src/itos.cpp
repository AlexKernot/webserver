/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itos.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:28:37 by akernot           #+#    #+#             */
/*   Updated: 2024/02/23 01:14:51 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "itos.hpp"

#include <string>

std::string itos(int n)
{
        long num = n;
        std::string tmp;
        bool negative = false;

        if (num == 0)
                return "0";
        if (num < 0) {
                num = -num;
                negative = true;
        }
        while (num != 0) {
                tmp += (num % 10) + '0';
                num /= 10;
        }
        if (negative)
                tmp += "-";
        std::string retval(tmp.rbegin(), tmp.rend());
        return retval;
}
