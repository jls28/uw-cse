make all
./buildfileindex ./test_tree/enron_email/ /tmp/butts
cd hw3fsck
make clean
make all
cd ..
./hw3fsck/hw3fsck /tmp/butts
