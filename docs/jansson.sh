git clone --branch v2.14 https://github.com/akheron/jansson.git
cd jansson
cmake .
make
sudo make install
cd ..
rm -rf jansson