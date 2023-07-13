#include <iostream>

using namespace std;


class CORHandler
{
    public:
        CORHandler * m_succesor;
        CORHandler(CORHandler * p_succesor)
		{
		    m_succesor = NULL;
		    if(p_succesor != NULL)
		    {
		        m_succesor = p_succesor;
		    }
		};
		~CORHandler() {};
        virtual void handle_request(bool b_can_u)
        {
	        std::cout << "Called the ancestor" << std::endl;
	        if(m_succesor != NULL)
	        {
	        	std::cout << "Succesor: " << m_succesor << std::endl;
        		m_succesor->handle_request(b_can_u);
	        }
        };
};

class CORSpecificHandler1 : public CORHandler
{
    public:
        CORSpecificHandler1(CORHandler * p_succesor) : CORHandler(p_succesor){};
		~CORSpecificHandler1() {};
        void handle_request(bool b_can_u)
		{
		    std::cout << "Request handled in COR1" << std::endl;
		}
        
};

class CORSpecificHandler2 : public CORHandler
{
    public:
        CORSpecificHandler2(CORHandler * p_succesor) : CORHandler(p_succesor){};
		~CORSpecificHandler2() {};
        void handle_request(bool b_can_u)
		{
		    if(b_can_u)
		    {
		        std::cout << "Request handled in COR2" << std::endl;
		    }
		    else
		    {
		        CORHandler::handle_request(b_can_u);
		    }
		}

        
};

int main() {

    CORSpecificHandler1 cor1(NULL);

	std::cout << "cor1: " << &cor1 << std::endl;
    CORSpecificHandler2 cor2(&cor1);
	std::cout << "cor2: " << &cor2 << std::endl;


	std::cout << "====1" << std::endl;
    cor2.handle_request(false);
	std::cout << "====2" << std::endl;
    cor2.handle_request(true);
	std::cout << "====3" << std::endl;

    return 0;
}