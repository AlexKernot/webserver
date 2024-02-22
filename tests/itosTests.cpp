/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itosTests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <akernot@student.42Adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 18:03:31 by akernot           #+#    #+#             */
/*   Updated: 2024/02/22 18:06:56 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <limits.h>

#include "../webserv/includes/itos.hpp"

TEST(itosTests, basic)
{
	ASSERT_EQ(itos(1), "1");
	ASSERT_EQ(itos(100), "100");
	ASSERT_EQ(itos(-42), "-42");
	ASSERT_EQ(itos(-700), "-700");
}

TEST(itosTests, edgeCases)
{
	ASSERT_EQ(itos(0), "0");
	ASSERT_EQ(itos(INT_MAX), "2147483647");
	ASSERT_EQ(itos(INT_MIN), "-2147483648");
}