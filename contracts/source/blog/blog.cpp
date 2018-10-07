#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using namespace std;

class blog : public contract
{

  public:
    using contract::contract;

    // Blog - POST, LIKE, COMMENT, FOLLOW

    [[eosio::action]] 
    void post(account_name poster, std::string content) {
        // Account (Posting the content), Content

        require_auth(poster); // Make sure that the account that is posting the content signs that trx
        print(content);
    }
};

// Macro that allows us to generate the ABI - eosio-cpp => eosio.cdt
EOSIO_ABI(blog, (post))
