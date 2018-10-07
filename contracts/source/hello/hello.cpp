// Include the required libraries into the file
// eosiolib/eosio.hpp loads the EOSIO C and C++ API into the scope of your contract
#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

// To make things more concise in your contract use namespace eosio.
using namespace eosio;

// Create a standard C++11 class. The contract class needs to extend eosio::contract.
class hello : public contract {

// Add a public access specifier and a using-declaration.
  public:
      using contract::contract;
       
     
      [[eosio::action]] 
      void hi( account_name user ) {
         print( "Hello World, ", name{user} );
         
      }
      
       // The above action accepts a parameter called user that's an account_name type.
};

// Finally, we need to add the EOSIO_ABI macro to handle the dispatching of actions for the hello contract.
EOSIO_ABI( hello, (hi))
