test -f $HOME/sdcc/bin/sdasstm8 && exit 0

sudo apt-get install subversion libboost-dev texinfo
svn checkout svn://svn.code.sf.net/p/sdcc/code/trunk/sdcc sdcc
cd sdcc
./configure --disable-pic14-port --disable-pic16-port --prefix=$HOME/sdcc
make
sudo make install
