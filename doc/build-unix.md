UNIX BUILD NOTES
====================
Some notes on how to build Securechain Wallet in Unix. 

To Build
---------------------

	./autogen.sh
	./configure
	make

This will build securechain-wallet as well if the dependencies are met.

Dependencies
---------------------

 Library     | Version        | Purpose          | Description
 ------------|----------------|------------------|--------------------------------------------------
 libssl      | 1.0.1k         | SSL Support      | Secure communications
 libdb4.8    | 4.8.30.NC      | Berkeley DB      | Wallet storage
 libboost    | 1.55.0         | Boost            | C++ Library
 miniupnpc   | 1.9.20140701   | UPnP Support     | Optional firewall-jumping support
 qt          | 4.6.4          | GUI              | GUI toolkit
 protobuf    | 2.5.0          | Payments in GUI  | Data interchange format used for payment protocol
 libqrencode | 3.4.3          | QR codes in GUI  | Optional for generating QR codes

[miniupnpc](http://miniupnp.free.fr/) may be used for UPnP port mapping.  It can be downloaded from [here](
http://miniupnp.tuxfamily.org/files/).  UPnP support is compiled in and
turned off by default.  See the configure options for upnp behavior desired:

	--without-miniupnpc      No UPnP support miniupnp not required
	--disable-upnp-default   (the default) UPnP support turned off by default at runtime
	--enable-upnp-default    UPnP support turned on by default at runtime

Licenses of statically linked libraries:
 Berkeley DB   New BSD license with additional requirement that linked
               software must be free open source
 Boost         MIT-like license
 miniupnpc     New (3-clause) BSD license

System requirements
--------------------

C++ compilers are memory-hungry. It is recommended to have at least 1 GB of
memory available when compiling Securechain Wallet. With 512MB of memory or less
compilation will take much longer due to swap thrashing.

Dependency Build Instructions: Ubuntu & Debian
----------------------------------------------
Build requirements:

	sudo apt-get install build-essential
	sudo apt-get install libtool autotools-dev autoconf
	sudo apt-get install libssl-dev


for Ubuntu 12.04 and later:

	sudo apt-get install libboost-all-dev

 db4.8 packages are available [here](http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz).

 Ubuntu 12.04 and later have packages for libdb5.1-dev and libdb5.1++-dev,
 but using these will break binary wallet compatibility, and is not recommended.

for Ubuntu 13.10:
	libboost1.54 will not work,
	remove libboost1.54-all-dev and install libboost1.53-all-dev instead.

for Debian 7 (Wheezy) and later:
 The oldstable repository contains db4.8 packages.
 Add the following line to /etc/apt/sources.list,
 replacing [mirror] with any official debian mirror.

	deb http://[mirror]/debian/ oldstable main

To enable the change run

	sudo apt-get update

for other Ubuntu & Debian:

	sudo apt-get install libdb4.8-dev
	sudo apt-get install libdb4.8++-dev

Optional:

	sudo apt-get install libminiupnpc-dev (see --with-miniupnpc and --enable-upnp-default)

Dependencies for the GUI: Ubuntu & Debian
-----------------------------------------

If you want to build securechain-wallet, make sure that the required packages for Qt development
are installed. Either Qt 4 or Qt 5 are necessary to build the GUI.
If both Qt 4 and Qt 5 are installed, Qt 4 will be used. Pass `--with-gui=qt5` to configure to choose Qt5.
To build without GUI pass `--without-gui`.

To build with Qt 4 you need the following:

    sudo apt-get install libqt4-dev libprotobuf-dev protobuf-compiler

For Qt 5 you need the following:

    sudo apt-get install libqt5gui5 libqt5core5 libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev

libqrencode (optional) can be installed with:

    sudo apt-get install libqrencode-dev

Once these are installed, they will be found by configure and a securechain-wallet executable will be
built by default.

Notes
-----
The release is built with GCC and then "strip securecoind" to strip the debug
symbols, which reduces the executable size by about 90%.


miniupnpc
---------
	tar -xzvf miniupnpc-1.6.tar.gz
	cd miniupnpc-1.6
	make
	sudo su
	make install


Berkeley DB
-----------
It is recommended to use Berkeley DB 4.8. If you have to build it yourself:

```bash
SECURECHAIN_WALLET_ROOT=$(pwd)

# Pick some path to install BDB to, here we create a directory within the securechain wallet directory
BDB_PREFIX="${SECURECHAIN_WALLET_ROOT}/db4"
mkdir -p $BDB_PREFIX

# Fetch the source and verify that it is not tampered with
wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'
echo '12edc0df75bf9abd7f82f821795bcee50f42cb2e5f76a6a281b85732798364ef  db-4.8.30.NC.tar.gz' | sha256sum -c
# -> db-4.8.30.NC.tar.gz: OK
tar -xzvf db-4.8.30.NC.tar.gz

# Build the library and install to our prefix
cd db-4.8.30.NC/build_unix/
#  Note: Do a static build so that it can be embedded into the exectuable, instead of having to find a .so at runtime
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=$BDB_PREFIX
make install

# Configure Securechain Wallet to use our own-built instance of BDB
cd $SECURECHAIN_WALLET_ROOT
./configure (other args...) LDFLAGS="-L${BDB_PREFIX}/lib/" CPPFLAGS="-I${BDB_PREFIX}/include/"
```

Alternatively to make a global build and installation:

cd build_unix/
../dist/configure --enable-cxx --disable-shared --with-pic --prefix=/usr/local
make
sudo make install

**Note**: You only need Berkeley DB if the wallet is enabled (see the section *Disable-Wallet mode* below).

Boost
-----
If you need to build Boost yourself:

	sudo su
	./bootstrap.sh
	./bjam install


Security
--------
To help make your securechain wallet installation more secure by making certain attacks 
impossible to exploit even if a vulnerability is found, binaries are hardened by default.
This can be disabled with:

Hardening Flags:

	./configure --enable-hardening
	./configure --disable-hardening


Hardening enables the following features:

* Position Independent Executable
    Build position independent code to take advantage of Address Space Layout Randomization
    offered by some kernels. An attacker who is able to cause execution of code at an arbitrary
    memory location is thwarted if he doesn't know where anything useful is located.
    The stack and heap are randomly located by default but this allows the code section to be
    randomly located as well.

    On an Amd64 processor where a library was not compiled with -fPIC, this will cause an error
    such as: "relocation R_X86_64_32 against `......' can not be used when making a shared object;"

    To test that you have built PIE executable, install scanelf, part of paxutils, and use:

    	scanelf -e ./securechain-wallet

    The output should contain:
     TYPE
    ET_DYN

* Non-executable Stack
    If the stack is executable then trivial stack based buffer overflow exploits are possible if
    vulnerable buffers are found. By default, securechain-wallet should be built with a non-executable
    stack but if one of the libraries it uses asks for an executable stack or someone makes a mistake
    and uses a compiler extension which requires an executable stack, it will silently build an
    executable without the non-executable stack protection.

    To verify that the stack is non-executable after compiling use:
    `scanelf -e ./securechain-wallet`

    the output should contain:
	STK/REL/PTL
	RW- R-- RW-

    The STK RW- means that the stack is readable and writeable but not executable.

Disable-wallet mode
--------------------
When the intention is to run only a P2P node without a wallet, securechain-wallet may be compiled in
disable-wallet mode with:

    ./configure --disable-wallet

In this case there is no dependency on Berkeley DB 4.8.

Mining is also possible in disable-wallet mode, but only using the `getblocktemplate` RPC
call not `getwork`.

