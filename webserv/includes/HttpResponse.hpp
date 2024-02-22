#ifndef HTTPRESPONSE_HPP
# define HTTPRESPONSE_HPP

# include "Ahttp.hpp"

class HttpResponse : public Ahttp {
public:
        HttpResponse(int socketFD);
        ~HttpResponse();

        int getStatusCode() const;
        void setStatusCode(int code);
        std::string getReasonPhrase() const;

        std::string build() const;

private:
        int statusCode;
        std::string reasonPhrase;

        HttpResponse();
        HttpResponse(const HttpResponse&);
        HttpResponse& operator=(const HttpResponse&);
};

#endif // HTTPRESPONSE_HPP
