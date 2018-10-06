# To get started:

## 1. Setup Working Directory

`mkdir hackathonprep && cd hackathonprep && mkdir contracts && cd contracts`

### Then copy the absolute path to the contracts folder.

`pwd`

## 2.Install Docker, pull eos docker image


`docker pull eosio/eos`

### This will download an Ubuntu image which contains the compiled software.

## 3. Boot Node and Wallet

### In the step 1 you created a `contracts` directory and obtained the absolute path.

### Replace both occurrences of "CONTRACTS_DIR" in the command below with the absolute path to your `contracts` directory.

`docker run --name eosio --publish 7777:7777 --publish 127.0.0.1:5555:5555 --volume CONTRACTS_DIR:CONTRACTS_DIR --detach eosio/eos /bin/bash -c "keosd --http-server-address=0.0.0.0:5555 & exec nodeos -e -p eosio --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:7777 --access-control-allow-origin=* --contracts-console --http-validate-host=false --filter-on='*'"`

### i.e for me, it was

`/home/shalomz/hackprep/contracts`

### So the command I run is

`docker run --name eosio --publish 7777:7777 --publish 127.0.0.1:5555:5555 --volume /home/shalomz/hackprep/contracts:/home/shalomz/hackprep/contracts --detach eosio/eos /bin/bash -c "keosd --http-server-address=0.0.0.0:5555 & exec nodeos -e -p eosio --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:7777 --access-control-allow-origin=* --contracts-console --http-validate-host=false --filter-on='*'"`

## 4. Check The installation

`docker logs --tail 10 eosio`

### The expected Output should be something like

    1929001ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366974ce4e2a... #13929 @ 2018-05-23T16:32:09.000 signed by eosio [trxs: 0, lib: 13928, confirmed: 0]
    1929502ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366aea085023... #13930 @ 2018-05-23T16:32:09.500 signed by eosio [trxs: 0, lib: 13929, confirmed: 0]
    1930002ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366b7f074fdd... #13931 @ 2018-05-23T16:32:10.000 signed by eosio [trxs: 0, lib: 13930, confirmed: 0]
    1930501ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366cd8222adb... #13932 @ 2018-05-23T16:32:10.500 signed by eosio [trxs: 0, lib: 13931, confirmed: 0]
    1931002ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366d5c1ec38d... #13933 @ 2018-05-23T16:32:11.000 signed by eosio [trxs: 0, lib: 13932, confirmed: 0]
    1931501ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366e45c1f235... #13934 @ 2018-05-23T16:32:11.500 signed by eosio [trxs: 0, lib: 13933, confirmed: 0]
    1932001ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000366f98adb324... #13935 @ 2018-05-23T16:32:12.000 signed by eosio [trxs: 0, lib: 13934, confirmed: 0]
    1932501ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 00003670a0f01daa... #13936 @ 2018-05-23T16:32:12.500 signed by eosio [trxs: 0, lib: 13935, confirmed: 0]
    1933001ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 00003671e8b36e1e... #13937 @ 2018-05-23T16:32:13.000 signed by eosio [trxs: 0, lib: 13936, confirmed: 0]
    1933501ms thread-0   producer_plugin.cpp:585       block_production_loo ] Produced block 0000367257fe1623... #13938 @ 2018-05-23T16:32:13.500 signed by eosio [trxs: 0, lib: 13937, confirmed: 0]

## Check the Wallet

### Run the following command on your terminal.

    docker exec -it eosio bash

    cleos --wallet-url http://127.0.0.1:5555 wallet list keys

### Expected Response:

    Wallets:
    []

You can exit the shell with

    exit

## 5. Alias Cleos

We won't want to enter into the Docker container's bash every time we want to interact with Nodeos or Keosd. So let's make cleos a bit easier to use.

You can either execute the following in your terminal for a temporary alias, or add it to your .bash_rc file if on Linux, or .profile file in on Mac OS if you wish for your alias to persist indefinitely.

    alias cleos='docker exec -it eosio /opt/eosio/bin/cleos --url http://127.0.0.1:7777 --wallet-url http://127.0.0.1:5555'

### NB:

To start/stop the container, and set up nodeos
  
 docker start eosio
docker stop eosio
docker exec -it nodeos

## 6. Build the CDT (Contract Development Toolkit)

### The EOSIO Contract Development Toolkit, CDT for short, is a collection of tools related to contract compilation.

### Subsequent tutorials use the CDT primarily for compiling contracts and generating ABIs.

    git clone --recursive https://github.com/eosio/eosio.cdt
    cd eosio.cdt

### When building the eosio.cdt, you need to define the symbol.

### From within the eosio.cdt folder, execute the following :

    ./build.sh SYS

### SYS is the symbol name that we are building the CDT with, though you could get fancy and define your own Symbol/Token

### After the CDT has been built, install the CDT

    sudo ./install.sh

Installing eosio.cdt will make the compiled binary global so it can be accessable anywhere.

# 7. Create a wallet

### The first step is to create a wallet. Use cleos wallet create to create a new "default" wallet using the option --to-console for simplicity.

### If using cleos in production, it's wise to instead use --to-file so your wallet password is not in your bash history. For development purposes and because these are development and not production keys --to-console poses no security threat.

    cleos wallet create --to-console

### cleos will return a password, save this password somewhere as you will likely need it later in the tutorial.

    NOTE:
    A common misconception in cryptocurrency regarding wallets is that they store tokens.

    A wallet does not store tokens. What a wallet does is store private keys in an encrypted file and sign transactions.

    A user builds a transaction object, usually through an interface, sends that object to the wallet to be signed,
    the wallet then returns that transaction object with a signature which is then broadcast to the network.

    When/if the network confirms that the transaction is valid, it is included into a block on the blockchain.

### To open a locked wallet

    cleos wallet open

### To view list of all wallets

    cleos wallet list

### To unlock a locked wallet

    cleos wallet unlock

### To create a key
    
    cleos wallet create_key

### To import a key into the wallet

    cleos wallet import
 
### You will be prompted for the private key.
### Enter the eosio development key

    5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3


# 8. Create Test Accounts

### An account is a collection of authorizations, stored on the blockchain, and used to identify a sender/recipient. 
### It has a flexible authorization structure that enables it to be owned either by an individual or group of individuals depending on how permissions have been configured. 
### An account is required to send or receive a valid transaction to the blockchain

### This tutorial series uses two "user" accounts, bob and alice, as well as the default eosio account for configuration. Additionally accounts are made for various contracts throughout this tutorial series.

### To create the user accounts bob and alice

    cleos create account eosio bob YOUR_PUBLIC_KEY 
    cleos create account eosio alice YOUR_PUBLIC_KEY

### Expected output

    executed transaction: 40c605006de...  200 bytes  153 us
    #         eosio <= eosio::newaccount            {"creator":"eosio","name":"alice","owner":{"threshold":1,"keys":[{"key":"EOS5rti4LTL53xptjgQBXv9HxyU...
    warning: transaction executed locally, but may not be confirmed by the network yet    ]

### You can fetch the details of the accounts

    cleos get account <ACCOUNT_NAME>


# 9. Smart Contracts - hello world!

### Borrowing from the definition of real-world contracts, we get to understand that a contract is an agreement that governs outcomes of actions, given a set of inputs.

### An EOSIO Smart contract, thence, is software that has been compiled in a format that is acceptable, executable and retrievable by EOS nodes. 
### Just as the name suggests, EOSIO Smart contracts borrow from the structure of traditional contracts, only that in the case of EOS Smart Contracts, the actions, parameters, data structures and the code that implements these aforementioned components are defined by the Smart Contract. All EOSIO Smart contracts are accompanied by Ricardian Contracts. We shall look at what Ricardian Contracts are shortly.


    A smart contract in EOS could be described as a collection of actions (steps that modify state) and tables (collections of state).

    A smart contract is bound to an entity, i.e A smart contract is associated to an account to which it has been deployed.

### Lets start. Will start with a hello world smart contract

#### Navigate to your contracts folder within your project folder, and create a file `hello.cpp`.

Write the following code into the file `hello.cpp`


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
    



#### You can then compile the code to web assembly
    eosio-cpp -o hello.wasm hello.cpp --abigen

#### When a contract is deployed, it is deployed to an account, and the account becomes the interface for the contract. To keep things simple, we will reuse the same keys we created before.

    NOTE:
    When a contract is deployed, it is deployed to an account, and the account becomes the interface for the contract. 
    As mentioned earlier these tutorials use the same public key for all of the accounts to keep things more simple.

To check the keys available in your wallet, run
    cleos wallet keys
    
If No keys are present, do the following:
    cleos create key --to-console
    cleos wallet import --private-key <PRIVATE_KEY>
    
#### Create an account for the contract using cleos create account, with the command provided below. Don't forget to replace YOUR_PUBLIC_KEY with the public key you generated earlier.

    cleos wallet import --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3  => This imports the eosio private key. If you get an error that keys exists already, just ignore.
    
    cleos create account eosio hello YOUR_PUBLIC_KEY -p eosio@active
    
#### Now deploy the contract to the account hello
    
    cleos set contract hello <CONTRACTS_DIR>hello -p hello@active
    
    Replace "CONTRACTS_DIR" in the command below with the absolute path to your `contracts` directory.
    
    
#### Try it out
     cleos push action hello hi '["hello"]' -p hello@active
    
    
    


