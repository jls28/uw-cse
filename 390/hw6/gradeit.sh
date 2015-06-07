i!/bin/bash
#for loop
MAX=$1
FILES="students/*"
echo "Retro Grade-It, 1970s version"
echo "Grading with a max score of $MAX"
echo
EXP="expected.txt"
for file in $FILES; do
  SCORE=$MAX
	STUDENT=`basename $file`
	echo "Processing $STUDENT ..."
  if [ -e $file/gettysburg.sh ]; then
    bash $file/gettysburg.sh 2>/dev/null > sout.txt
    #echo `cat sout.txt`
    DIFF=`diff -w sout.txt expected.txt | grep "[<>]" | wc -l`
    COMMENTS=`cat $file/gettysburg.sh 2>/dev/null | grep "#" | wc -l`
    #echo $DIFF
    if [ $DIFF -eq 0 ]; then
      echo "$STUDENT has correct output"
    else
      echo "$STUDENT has incorrect output (`echo $DIFF` lines do not match)"
    fi
    let "DIFF *= 5"
    let "SCORE -= $DIFF"
    if [ $COMMENTS -lt 3 ]; then
        let "SCORE -= 7"
    fi
    if [ $SCORE -lt 0 ]; then
      let "SCORE = 0"
    fi
    echo $STUDENT has $COMMENTS lines of comments
  else
    echo "$STUDENT did not turn in the assignment"
    let "SCORE = 0"
  fi
  echo "$STUDENT has earn a score $SCORE / 50"
  rm sout.txt 2>/dev/null
  echo
done
