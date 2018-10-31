Securechain Wallet Release Notes
====================

0.10.0
---------------------
- Removed support for TXCOMMENT_VERSION to save precious transaction space.
  Compared with currency transfer, the value of message bytes is quite low,
  which makes it a hugh waste to consume the same PoW energy on it.
  As TXCOMMENT_VERSION has never been released, such change will not result
  in a hard fork.
- Removed price adjustment as the block approaches full. The change aligns
  with the update from Bitcoin-Core 0.8.6 to 0.9.
- In walletdb.cpp, the new "pubkey.privkey" pair is hashed by Hash9.
- To CBlockHeader, we use even number for CURRENT_VERSION to indicate stable 
  release.
- The unit test cases for TestNet and script addrType should be added in the
  future.
- The unit test case of "and one which spends it" for bloom_match should be
  added in the future.
- The unit test cases of "miner_tests" should be added in the future.
- The unit test case of "rpc_rawsign" for rpc_tests should be added in the
  future.
- Some special tx cases can be added to "tx_valid.json" in the future,
  especially for P2SH transactions.
- Fixed bug in FormatMoney, which is mainly used for debug logging feature.

  

0.9.2
---------------------
- Fixed DNS seed server issue
- Updated build process

0.9.1 (Pre-release)
---------------------
- Supported creating multiple receiving addresses simultaneously

0.9.0
---------------------

- Upgraded OpenSSL version to fix Heartbleed security issue
- Fixed Mac OSX compilation issues
- Supported fetching block/transaction/address details from securechain.info
- Supported static compilation for both Windows and Mac versions
- Applied digital code signing to both Windows and Mac versions