#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

# include <string>

# include "Ahttp.hpp"
# include "IServible.hpp"

class AHttpRequest : public Ahttp, public IServible {
public:
        AHttpRequest(int socketFD);
        ~AHttpRequest();

        // override
        std::string build() const;
        // no override
        // Ahttp *serve(Config &config);
        virtual std::string getMethodString() const = 0;
        virtual Config::methods getMethod() const = 0;

        std::string getURI() const;
        void setURI(std::string uri);
private:
        // TODO: Make into seperate class
	std::string absoluteURI;

        AHttpRequest();
        AHttpRequest(const AHttpRequest&);
        AHttpRequest& operator=(const AHttpRequest&);
};

#endif // HTTPREQUEST_HPP
