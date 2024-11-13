/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdStream.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:33:30 by akernot           #+#    #+#             */
/*   Updated: 2024/03/11 18:38:18 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_HPP
#define GNL_HPP

#include <iostream>
#include <string>

class FdStream
{
private:
    int fd;
    char *readBuffer;
    std::string lineBuffer;
    static const int bufferSize = 1024;
    enum errorTypes {none, BadFile, EoF, Error};
    errorTypes errorState;

    void setBad();
    void setEOF();
    void setFail();

    std::string readUntilNl();

public:
    FdStream(int fd); 
    ~FdStream();

    std::string readLine();

    bool getBadFile() const; 
    bool getEOF() const; 
    bool getError() const; 

    int getErrorState() const;
};

#endif
