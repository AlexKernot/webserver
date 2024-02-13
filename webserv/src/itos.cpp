/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itos.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:28:37 by akernot           #+#    #+#             */
/*   Updated: 2024/02/13 15:14:55 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

static int reverse(int n) {
        int retval = 0;

        while (n != 0) {
                retval *= 10;
                retval += n % 10;
                n /= 10;
        }
        return retval;
}

std::string itos(int n)
{
        std::string retval;
        int reversed = reverse(n);

        if (n == 0)
                return "0";
        while (reversed != 0) {
                retval += (reversed % 10) + '0';
                reversed /= 10;
        }
        return retval;
}
