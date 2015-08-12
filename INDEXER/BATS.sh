# Pritika Vig
# BATS.sh
# Lab 5: Indexer


# 1 test input parameters
# 2 clean build indexer
# 3 test input parameters
# 4 test indexer in both the original and testing mode and compare the index files




# 1. specify the log file

logfile=indexTestLog.$(date +"%a_%b_%d_%T_%Y")
datapath=./src/data/
indexfile=index.dat
reIndexfile=reInd.dat

echo "start testing indexer" >> $logfile

# 2. clean build the indexer

#make clean >> $logfile
#make indexer >> $logfile

#if [$? -ne 0 ]; then 
#	echo "Error in build" >> $logfile
#	exit 1
#fi

echo "Successfully built indexer." >> $logfile

# 3. test input parameters
echo -e "\n" >> $logfile
echo "Test input parameters:" >> $logfile

index invaliddir $indexfile >> $logfile

index $datapath too many arguments >> $logfile

echo -e "\n" >> $logfile

# 4. test indexer in testing mode and compare results
# run indexer
index $datapath $indexfile $reIndexfile
# sort index and tmpnewindex
sort $indexfile > test1
sort $reIndexfile > test2
# check diff between two files

echo "Number of differences in Index file and Reindex file: " >> $logfile
diff test1 test2
echo $? >> $logfile

# clean up
rm -f test1 test2 $indexfile $reIndexfile


