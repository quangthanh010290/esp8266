sudo apt-get install make unrar autoconf automake libtool gcc g++ gperf \
    flex bison texinfo gawk ncurses-dev libexpat-dev python python-serial sed \
    git unzip
git clone --recursive https://github.com/pfalcon/esp-open-sdk.git
cd esp-open-sdk
unset LD_LIBRARY_PATH
make
