# testCrawl.sh
# Pritika Vig
# Lab 4 : Crawler


# Create Test Header
filename=crawlerTestLog.$(date +"%a_%b_%d_%T_%Y")

echo Pritika Vig > $filename
echo " " >> $filename


# Test with incorrect number of arguments
echo "Testing for too many args. Shoud exit:"  >> $filename
./crawler  too many 4 arguments >> $filename
echo " " >> $filename
echo " " >> $filename


# Test with bad directory
echo "Testing for invalid dir. Should exit:"  >> $filename
./crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ dir 2 >> $filename
echo " " >> $filename

# Test with large depth
echo "Testing for oversized depth. Should exit:"  >> $filename
./crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ testHold/ 6 >> $filename
echo " " >> $filename

# Test for invalid domain
echo " " >> $filename
echo "Testing for invalid domain. Should exit:"  >> $filename
./crawler http://google.com data/ 2 >> $filename
echo " " >> $filename


# Test with depth 1, root dir
echo "Testing for success, should be silent:"  >> $filename
./crawler http://old-www.cs.dartmouth.edu/~cs50/tse/ testHold/ 1 >> $filename