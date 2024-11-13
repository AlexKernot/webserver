/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdStream.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akernot <a1885158@adelaide.edu.au>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:30:30 by akernot           #+#    #+#             */
/*   Updated: 2024/03/11 20:35:30 by akernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FdStream.hpp"
#include <unistd.h>
#include <stdlib.h>
#include <cstring>

FdStream::FdStream(int fd)
{
	this->fd = fd;
	this->errorState = none;

	readBuffer = new char[bufferSize + 1];
	if (readBuffer == NULL)
		setFail();
}

FdStream::~FdStream()
{
	free(readBuffer);
}

std::string FdStream::readUntilNl()
{
        ssize_t bytesRead = read(fd, readBuffer, bufferSize);
        if (bytesRead == -1) {
                setFail();
                return "";
        }
        // search for the \n
        char *newl = std::strchr(readBuffer, '\n');
        if (bytesRead > bufferSize)
                setEOF();
        if (newl != NULL) {
                std::string retval(lineBuffer);
                lineBuffer = readBuffer;
                std::size_t pos = lineBuffer.find('\n'); // noexcept
                try {
                        retval += lineBuffer.substr(0, pos);
                        lineBuffer = lineBuffer.substr(pos + 1);
                } catch (const std::bad_alloc&) {
                        setFail();
                        return "";
                }
                return retval;
        }
        lineBuffer += readBuffer;
        if (getEOF() == true)
                return lineBuffer;
        bytesRead = read(fd, readBuffer, bufferSize);
        newl = std::strchr(readBuffer, '\n');

        // Tail recursion until new line or end of file
        return readUntilNl();
}

std::string FdStream::readLine()
{
        // Check if there is already a new line in the buffer
        std::size_t pos = lineBuffer.find('\n'); // noexcept
        if (pos != std::string::npos) {
                // Seperate string up to the new line and return the full line
                try {
                        std::string retval(lineBuffer.substr(0, pos));
                        lineBuffer = lineBuffer.substr(pos + 1);
                        return retval;
                } catch (const std::bad_alloc&) {
                        setFail();
                        return "";
                }
        }
        return readUntilNl();
}

bool FdStream::getBadFile() const
{
	if (errorState == BadFile)
		return (true);
	return (false);
}

bool FdStream::getEOF() const
{
	if (errorState == EoF)
		return (true);
	return (false);
}

bool FdStream::getError() const
{
	if (errorState == Error)
		return (true);
	return (false);
}

int FdStream::getErrorState() const
{
	return (errorState);
}

void FdStream::setBad()
{
	errorState = BadFile;
}

void FdStream::setEOF()
{
	errorState = EoF;
}

void FdStream::setFail()
{
	errorState = Error;
	// * Not allowed to check errno after read
	// // std::cerr << "FdStream error: " << strerror(errno) << std::endl;
}
