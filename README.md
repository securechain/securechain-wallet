Securechain Wallet 0.9.2
====================

[![Join the chat at https://gitter.im/Securechain/Lobby](https://badges.gitter.im/Securechain/Lobby.svg)](https://gitter.im/Securechain/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2013-2014 SecureCoin Developers
Copyright (c) 2015-2017 Securechain Developers

Distributed under the MIT/X11 software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](http://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), UPnP software written by Thomas Bernard and
sphlib 3.0 by Thomas Pornin.


Intro
---------------------
Securechain wallet is the official Securecoin wallet. Securecoin is a
free open source peer-to-peer electronic cash system that is
completely decentralized, without the need for a central server or trusted
parties.  Users hold the crypto keys to their own money and transact directly
with each other, with the help of a P2P network to check for double-spending. It is secured by six different algorithms and its CPU only mining is another security strength. 


Setup
---------------------
You need the Qt5 run-time and probably boost libraries to run Securechain Wallet. On Debian or Ubuntu:
	`sudo apt-get install libqt5gui5`

This release supports all Windows, Mac and Linux compilation.


Build
---------------------
The recommended versions of dependencies:

```
boost: 1.60
openssl: 1.0.2
miniupnpc: 1.9.20150522 or previous 1.9 version
Berkeley DB: 4.8.30NC
```

Before build, please make a clone of Securechain Wallet source code to your local machine as below:

```
git clone https://github.com/securechain/securechain-wallet.git
```

### Securechain Wallet GUI

**Windows (static)**

To build a Windows version, it is recommended to setup a [MXE](http://mxe.cc/) environment under Ubuntu Linux 16.04. Try the steps below with reference to "https://bitcointalk.org/index.php?topic=1080289.0":

1. Open a terminal and install all dependency libraries with root privilege as below (http://mxe.cc/#requirements-debian):

```
sudo apt-get install \
autoconf automake autopoint bash bison bzip2 flex gettext\
git g++ gperf intltool libffi-dev libgdk-pixbuf2.0-dev \
libtool-bin libltdl-dev libssl-dev libxml-parser-perl make \
openssl p7zip-full patch perl pkg-config python ruby scons \
sed unzip wget xz-utils g++-multilib libc6-dev-i386
```

2. Download the latest version of MXE as below (http://mxe.cc/#download):

```
git clone https://github.com/mxe/mxe.git
```

3. Perform static boost, qttools and miniupnpc compilation by MXE as below:

```
make MXE_TARGETS="i686-w64-mingw32.static" boost
make MXE_TARGETS="i686-w64-mingw32.static" qttools
make MXE_TARGETS="i686-w64-mingw32.static" miniupnpc
```

Note that the current version of miniupnpc from MXE works fine for Securechain Wallet, so that there is no need to perform manual compilation.

4. Download Berkeley DB 4.8.30NC from http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz and extract to db-4.8.30.NC folder.

5. Copy "securechain-wallet/compile-db.sh" file to the db-4.8.30.NC folder and update the "MXE_PATH" environment variable in the file.

6. Open a terminal and go to the same folder, and then run the following command to perform static cross compilation by MXE:

```
./compile-db.sh
```

7. Go to securechain-wallet folder, open "compile-src.sh" and update the "MXE_PATH" environment variable.

8. In the same terminal go to the "securechain-wallet" folder, then run the following command:

```
./comiple-src.sh
```

9. When the build is finished, there will be a new "securechain-wallet.exe" file under the "release" folder. The new file can run on Windows.


**Linux (non-static)**

It is recommended to build a Linux version under Ubuntu 16.04. Try the steps below:

1. Install all dependencies including boost, qttools, miniupnpc and openssl by Apt tools.

2. Make and install Berkeley DB by manually.

3. Start Qt Creator and open "securechain-wallet.pro", then make proper configurations. Be sure that it is a release build.

4. Use the "Build"/"Build All" menu option to start the build.

5. When the build is finished, there will be a new "securechain-wallet" file under the "build-securechain-wallet-Desktop-Release" folder. The new file can run on the same Linux platform.


**Mac (static)**

The build steps for Mac are similar to those on Linux. Note that due to the new [System Integrity Protection](https://support.apple.com/en-us/HT204899) feature from EI Capitan, the "/usr" and "/usr/local" folders may be read-only even with root privilege. Therefore it is recommended to install the dependencies into "/opt/local" folder. Some libraries can also be installed automatically by [MacPort](https://www.macports.org/).

Note that the build for Mac will be static, therefore the dependencies should also be static including Qt. To make a static build of Qt libraries, please refer to http://doc.qt.io/qt-5/osx-deployment.html

To deploy the software, please add "RELEASE=1" as an additional argument to qmake in build setting.


### SecureCoin Daemon (Not fully tested)

**Linux**

It is recommended to build a Linux version under Ubuntu 16.04. Try the steps below:

1. Install the same dependencies as to Securechain Wallet GUI.

2. Open a terminal and go to "securechain-wallet/src" folder, then run the following command:

```
make -f makefile.unix
```

3. When the build is finished, there will be a new "securecoind" file under the same folder. The new file can run on the same Linux platform.

**Mac**

The build steps for Mac are similar to those on Linux. The only change is to use the osx makefile as below:

```
make -f makefile.osx
```

For more information please refer to the Mac section for Securechain Wallet GUI.


Developers
---------------------
The main developer of SecureCoin core wallet is baritus.

The main developer of Securechain Wallet is Haimin Zhang ([contact@securechain.com](mailto:contact@securechain.com)) and Baritus.


Other Pages
---------------------
- [Unix Build Notes](build-unix.md)
- [OSX Build Notes](build-osx.md)
- [Windows Build Notes](build-msw.md)
- [Coding Guidelines](coding.md)
- [Release Process](release-process.md)
- [Release Notes](release-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Unit Tests](unit-tests.md)
- [Translation Process](translation_process.md)
