# Pritika Vig
# BATS.sh
# Lab 5: Indexer


# 1 test input parameters
# 2 clean build indexer
# 3 test input parameters
# 4 test indexer in both the original and testing mode and compare the index files




# 1. specify the log file

logfile=indexTestLog.$(date +"%a_%b_%d_%T_%Y")
datapath=../data
indexfile=index.dat

echo "start testing indexer" >> $logfile

# 2. clean build the indexer

make clean >> $logfile
make indexer >> $logfile

if [$? -ne 0 ]; then 
	echo "Error in build" >> $logfile
	exit 1
fi

echo "Successfully built indexer." >> $logfile

# 3. test input parameters

echo "test input parameters" >> $logfile



# 4. test indexer in testing mode and compare results
# run indexer
./indexer $datapath ./index.dat ./tmpnewindex.dat
# sort index and tmpnewindex
# check diff between two files
	# exit status 0 means they are the same